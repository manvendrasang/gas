#include "Voice.h"

#include <algorithm>
#include <cmath>

#include "oscillators/SineOscillator.h"
#include "oscillators/SquareOscillator.h"
#include "oscillators/SawOscillator.h"
#include "oscillators/TriangleOscillator.h"
#include "oscillators/NoiseOscillator.h"
#include "MidiUtils.h"
#include "StereoPanner.h"

std::unique_ptr<Oscillator>
Voice::createOscillator(
    WaveType type)
{
    switch (type)
    {
        case WaveType::Sine:
            return
                std::make_unique<SineOscillator>();

        case WaveType::Square:
            return
                std::make_unique<SquareOscillator>();

        case WaveType::Saw:
            return
                std::make_unique<SawOscillator>();

        case WaveType::Triangle:
            return
                std::make_unique<TriangleOscillator>();

        case WaveType::Noise:
            return
                std::make_unique<NoiseOscillator>();
    }

    return
        std::make_unique<SineOscillator>();
}

void Voice::prepare(
    double sr)
{
    sampleRate = sr;

    oscillators.prepare(sr);

    processor.prepare(sr);

    vibratoLFO.prepare(sr);
}

void Voice::reset()
{
    state = VoiceState{};

    info = VoiceInfo{};

    unisonIndex = 0;

    unisonCount = 1;
}

void Voice::setInstrument(
    const Instrument& inst)
{
    reset();

    instrument = inst;

    state.currentFrequency =
    info.frequency;

    oscillators.setPrimary(
        createOscillator(
            inst.waveType));

    oscillators.setPrimaryGain(
        1.0f);

    // Secondary oscillator: only instantiated when it will
    // actually be heard. Always explicitly cleared otherwise,
    // since the OscillatorBank is reused across notes and a
    // stale oscillator/gain from a previous instrument must
    // never bleed into this one.
    if (inst.secondaryVolume > 0.0f)
    {
        oscillators.setSecondary(
            createOscillator(
                inst.secondaryWaveType));

        oscillators.setSecondaryGain(
            inst.secondaryVolume);
    }
    else
    {
        oscillators.setSecondary(
            nullptr);

        oscillators.setSecondaryGain(
            0.0f);
    }

    // Sub oscillator: reuses the primary wave shape, pitched
    // to track subOctaveOffset relative to the current note.
    if (inst.subEnabled)
    {
        oscillators.setSub(
            createOscillator(
                inst.waveType));

        oscillators.setSubGain(
            inst.subVolume);
    }
    else
    {
        oscillators.setSub(
            nullptr);

        oscillators.setSubGain(
            0.0f);
    }

    oscillators.setPrimaryFrequency(
        inst.frequency);

    // Stage 16 - LFO Core. vibratoLFO is a Voice-level member
    // (not part of VoiceState/reset()), so its phase naturally
    // free-runs across notes by default - vibratoSync == true
    // (the default) explicitly resets it here instead, giving
    // every note the same, predictable vibrato onset.
    vibratoLFO.setFrequency(
        inst.vibratoSpeed);

    vibratoLFO.setDepth(
        inst.vibratoDepth);

    vibratoLFO.setShape(
        inst.vibratoShape);

    if (inst.vibratoSync)
    {
        vibratoLFO.reset();
    }

    processor.setEnvelope(
        inst.envelope);

    noteOn();

    processor.setFilters(
        inst.lowpassCutoff,
        inst.highpassCutoff);

    processor.setBitCrush(
        inst.bitCrush);
}

void Voice::setUnisonSlot(
    int index,
    int count)
{
    unisonIndex = index;

    unisonCount = count;
}

StereoSample Voice::process()
{
    state.time +=
        1.0f /
        static_cast<float>(sampleRate);

    incrementAge();

    // Stage 14 - Portamento. Advance an in-progress glide before
    // state.currentFrequency is used for anything below.
    // glideDuration defaults to 0 (set by setMidiNote() and by
    // VoiceState's own defaults), so this is a no-op for every
    // voice that never had glideToMidiNote() called on it -
    // state.currentFrequency was already set directly and stays
    // untouched here, exactly like Stage 11/12/13.
    if (state.glideDuration > 0.0f)
    {
        state.glideElapsed +=
            1.0f /
            static_cast<float>(sampleRate);

        if (state.glideElapsed >= state.glideDuration)
        {
            // Glide finished this sample - snap exactly to the
            // target and stop tracking it, so we don't keep
            // doing this division every sample forever.
            state.currentFrequency =
                state.glideTargetFrequency;

            state.glideDuration =
                0.0f;
        }
        else
        {
            const float t =
                state.glideElapsed /
                state.glideDuration;

            // Linear interpolation in log2(frequency), i.e.
            // exponential in Hz - this gives a constant musical
            // glide speed regardless of interval size, so a
            // glide across an octave doesn't sound dramatically
            // faster or slower than a glide across a semitone.
            const float startLog =
                std::log2(
                    state.glideStartFrequency);

            const float targetLog =
                std::log2(
                    state.glideTargetFrequency);

            state.currentFrequency =
                std::exp2(
                    startLog +
                    (targetLog - startLog) * t);
        }
    }

    // Stage 16 - LFO Core. Vibrato modulates the note's base
    // pitch, before unison detune / secondary / sub are derived
    // from it - so the whole voice wobbles together in pitch,
    // rather than only one oscillator layer. vibratoLFO.process()
    // returns depth * waveform(-1..1); depth is in Hz, matching
    // how instrument.vibratoDepth was already documented/passed
    // around even before this stage actually implemented it.
    // With the default vibratoDepth of 0.0, this returns exactly
    // 0.0 every time - a complete no-op for every existing
    // instrument that hasn't set it, identical to Stage 11-15.
    const float vibratoModulatedFrequency =
        state.currentFrequency +
        vibratoLFO.process();

    // Stage 13 - 8-Voice Unison. When this voice is part of a
    // unison stack (unisonCount > 1), it sits at an evenly
    // spread position across the stack: voice 0 and voice
    // (count-1) sit at the extremes (-1 and +1), the rest fill
    // in evenly between them. That single spread value drives
    // both this voice's detune (below) and its stereo position
    // (further down). unisonCount defaults to 1, which collapses
    // spread to 0 and matches Stage 11/12 behavior exactly.
    float unisonSpread =
        0.0f;

    if (unisonCount > 1)
    {
        unisonSpread =
            (2.0f *
             static_cast<float>(unisonIndex)) /
            static_cast<float>(unisonCount - 1)
            - 1.0f;
    }

    const float primaryFrequency =
        vibratoModulatedFrequency *
        MidiUtils::centsToRatio(
            unisonSpread *
            instrument.unisonDetune);

    oscillators.setPrimaryFrequency(
        primaryFrequency);

    // Secondary tracks the current pitch, detuned by a fixed
    // number of cents - this is what makes it a genuine detune
    // rather than an independent fixed-frequency oscillator.
    oscillators.setSecondaryFrequency(
        primaryFrequency *
        MidiUtils::centsToRatio(
            instrument.secondaryDetune));

    // Sub tracks the current pitch, offset by whole octaves.
    // Expressing the octave offset as cents (1200 cents per
    // octave) lets it reuse the same ratio helper.
    oscillators.setSubFrequency(
        primaryFrequency *
        MidiUtils::centsToRatio(
            static_cast<float>(
                instrument.subOctaveOffset) *
            1200.0f));

    oscillators.setDutyCycle(
        instrument.squareDuty);

    float sample =
        oscillators.process();

    sample =
        processor.process(
            sample);

    sample *=
        instrument.volume *
        info.velocity;

    // Stage 13 - 8-Voice Unison gain staging. Summing N unison
    // voices without correction can be up to N times louder than
    // a single voice in the worst case (voices nearly in phase
    // at low detune). Scaling each voice's contribution by 1/N
    // guarantees the summed unison stack never exceeds a single
    // voice's peak amplitude, the same "only ever scale down"
    // philosophy OscillatorBank's gain staging already uses.
    // unisonCount defaults to 1, so this is a no-op for every
    // instrument that hasn't opted into unison.
    sample /=
        static_cast<float>(
            unisonCount);

    // Stage 12 - Stereo Spread / Stage 13 - 8-Voice Unison.
    // Panning happens last, after the full mono signal chain
    // (oscillators, filters, envelope, effects) is finished, so
    // the DSP itself is unaffected by either stage - only the
    // final placement in the stereo field changes. With no
    // unison active (unisonCount == 1, the default), this is
    // exactly Stage 12's note-based pan. With unison active,
    // each voice in the stack gets its own fixed position spread
    // evenly across the field instead - the note-based pan is
    // what a single, un-detuned voice would use, so it isn't
    // meaningful once there are several deliberately-detuned
    // voices to place instead.
    const float panPosition =
        (unisonCount > 1)
        ? unisonSpread *
          std::clamp(
              instrument.stereoWidth,
              0.0f,
              1.0f)
        : StereoPanner::computePan(
              info.midiNote,
              instrument.stereoWidth);

    return
        StereoPanner::pan(
            sample,
            panPosition);
}

void Voice::setMidiNote(
    int midiNote)
{
    info.midiNote =
        midiNote;

    info.frequency =
        MidiUtils::noteToFrequency(
            midiNote);

    state.currentFrequency =
        info.frequency;

    // Stage 14 - Portamento. An instant jump means no glide is
    // in progress - explicitly clearing these (rather than
    // relying on setInstrument()'s reset() to have already done
    // it) keeps that invariant true regardless of call order.
    state.glideStartFrequency =
        info.frequency;

    state.glideTargetFrequency =
        info.frequency;

    state.glideDuration =
        0.0f;

    state.glideElapsed =
        0.0f;
}

void Voice::glideToMidiNote(
    int midiNote,
    float fromFrequency,
    float glideTimeSeconds)
{
    info.midiNote =
        midiNote;

    info.frequency =
        MidiUtils::noteToFrequency(
            midiNote);

    if (glideTimeSeconds > 0.0f &&
        fromFrequency > 0.0f)
    {
        state.currentFrequency =
            fromFrequency;

        state.glideStartFrequency =
            fromFrequency;

        state.glideTargetFrequency =
            info.frequency;

        state.glideDuration =
            glideTimeSeconds;

        state.glideElapsed =
            0.0f;
    }
    else
    {
        // No meaningful glide requested (or no valid starting
        // pitch to glide from) - fall back to exactly the same
        // instant jump as setMidiNote().
        state.currentFrequency =
            info.frequency;

        state.glideStartFrequency =
            info.frequency;

        state.glideTargetFrequency =
            info.frequency;

        state.glideDuration =
            0.0f;

        state.glideElapsed =
            0.0f;
    }
}

int Voice::getMidiNote() const
{
    return
        info.midiNote;
}

float Voice::getFrequency() const
{
    return
        info.frequency;
}

float Voice::getCurrentFrequency() const
{
    return
        state.currentFrequency;
}

bool Voice::isActive() const
{
    return info.active;
}

void Voice::setActive(
    bool active)
{
    info.active = active;
}

void Voice::setReleased(
    bool released)
{
    info.released = released;
}

bool Voice::isReleased() const
{
    return info.released;
}

void Voice::setSustained(
    bool sustained)
{
    info.sustained = sustained;
}

bool Voice::isSustained() const
{
    return info.sustained;
}

unsigned long Voice::getAge() const
{
    return info.age;
}

void Voice::incrementAge()
{
    ++info.age;
}

void Voice::resetAge()
{
    info.age = 0;
}

void Voice::noteOn()
{
    processor.noteOn();
}

void Voice::noteOff()
{
    processor.noteOff();
}

bool Voice::finished() const
{
    return
        !processor.isActive();
}

void Voice::setVelocity(
    float velocity)
{
    info.velocity = velocity;
}

float Voice::getVelocity() const
{
    return info.velocity;
}

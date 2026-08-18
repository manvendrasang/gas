#include "VoiceManager.h"

#include <algorithm>

VoiceManager::VoiceManager(
    int maxVoices)
    :
    voices(maxVoices)
{
}

void VoiceManager::prepare(
    double sampleRate)
{
    this->sampleRate = sampleRate;

    for (auto& voice : voices)
    {
        voice.prepare(sampleRate);
    }
}

void VoiceManager::noteOn(
    int midiNote,
    float velocity,
    const Instrument& instrument)
{
    // Stage 13 - 8-Voice Unison. A single note now spawns
    // unisonCount actual Voice instances instead of always one,
    // each assigned its slot within the stack via
    // setUnisonSlot() - that is what drives their individual
    // detune and stereo position (see Voice::process()). All of
    // them share midiNote, so noteOff() below releases the whole
    // stack together. unisonVoices defaults to 1, so this loop
    // runs once per note exactly as before for every instrument
    // that hasn't opted into unison.
    const int unisonCount =
        std::clamp(
            instrument.unisonVoices,
            1,
            8);

    for (int slot = 0; slot < unisonCount; ++slot)
    {
        int index = -1;

        for (size_t i = 0; i < voices.size(); ++i)
        {
            if (!voices[i].isActive())
            {
                index = static_cast<int>(i);
                break;
            }
        }

        // Stage 15 - Improved Voice Stealing. If no free voice
        // was found, we have to steal one that's already
        // sounding. Choose it based on the pool's real state
        // (release status + age) rather than a round-robin index
        // - specifically, prefer a voice that's already fading
        // out in its release tail (least audible to interrupt),
        // and among equally-eligible voices prefer the oldest.
        const bool stolen =
            (index == -1);

        float stolenFromFrequency =
            0.0f;

        if (stolen)
        {
            std::vector<bool> released(
                voices.size());

            std::vector<unsigned long> ages(
                voices.size());

            for (size_t i = 0; i < voices.size(); ++i)
            {
                released[i] =
                    voices[i].isReleased();

                ages[i] =
                    voices[i].getAge();
            }

            index =
                VoiceAllocator::chooseVoiceToSteal(
                    released,
                    ages);

            // Stage 14 - Portamento. Captured before
            // setInstrument() below, which internally resets the
            // voice's state - this is the voice's real current
            // pitch (possibly itself mid-glide), not just its
            // nominal note frequency.
            stolenFromFrequency =
                voices[index].getCurrentFrequency();
        }

        // setInstrument() performs its own internal reset() of
        // the voice's per-note state (VoiceInfo and unison
        // slot), so the note-specific calls below must come
        // after it - otherwise they get wiped and every voice
        // silently falls back to its defaults (midiNote 69,
        // velocity 1.0, unison slot 0 of 1) regardless of what
        // was actually requested here.
        voices[index].setInstrument(
            instrument);

        voices[index].setReleased(false);

        voices[index].setSustained(false);

        voices[index].setVelocity(
            velocity);

        if (stolen &&
            instrument.portamentoTime > 0.0f)
        {
            voices[index].glideToMidiNote(
                midiNote,
                stolenFromFrequency,
                instrument.portamentoTime);
        }
        else
        {
            voices[index].setMidiNote(
                midiNote);
        }

        voices[index].setUnisonSlot(
            slot,
            unisonCount);

        // Stage 18 - Pitch Bend. A voice's pitchBendValue is a
        // Voice-level member that setInstrument()'s reset()
        // doesn't touch (deliberately - see Voice.h), so a
        // stolen/reused voice would otherwise keep carrying
        // whatever bend it happened to have from its previous
        // note. Explicitly re-applying the currently-held channel
        // bend here means a note played while the pitch wheel is
        // already deflected starts bent correctly, whether this
        // voice is brand new or reused.
        voices[index].setPitchBend(
            currentPitchBend);

        // Stage 19 - Mod Wheel. Same re-apply-on-note-on
        // reasoning as pitch bend above.
        voices[index].setModWheel(
            currentModWheel);

        voices[index].setActive(true);
    }
}

void VoiceManager::noteOff(
    int midiNote)
{
    // Stage 13 - 8-Voice Unison. A note may now be backed by
    // several voices (its whole unison stack), all sharing
    // midiNote, so every matching active voice must be released
    // here - not just the first one found. Before unison this
    // was always exactly one voice, so the old early "break"
    // never mattered; with unison it would have left every voice
    // but one stuck sounding indefinitely.
    for (auto& voice : voices)
    {
        if (voice.isActive() &&
            voice.getMidiNote() == midiNote)
        {
            voice.setReleased(true);

            voice.noteOff();
        }
    }
}

void VoiceManager::setPitchBend(
    float value)
{
    currentPitchBend = value;

    // Applies immediately to every currently-active voice -
    // pitch bend is a real-time performance control, not
    // something that should wait for the next note-on to take
    // effect. Voices that aren't active yet will pick up
    // currentPitchBend when they're triggered, in noteOn() above.
    for (auto& voice : voices)
    {
        if (voice.isActive())
        {
            voice.setPitchBend(
                value);
        }
    }
}

void VoiceManager::setModWheel(
    float value)
{
    currentModWheel = value;

    for (auto& voice : voices)
    {
        if (voice.isActive())
        {
            voice.setModWheel(
                value);
        }
    }
}

StereoSample VoiceManager::process()
{
    StereoSample output;

    for (size_t i = 0; i < voices.size(); ++i)
    {
        auto& voice = voices[i];

        if (!voice.isActive())
            continue;

        output += voice.process();

        if (voice.finished())
        {
            voice.setActive(false);
        }
    }

    return output;
}
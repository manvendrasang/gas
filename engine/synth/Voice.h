#pragma once

#include <memory>

#include "Instrument.h"
#include "Oscillator.h"
#include "OscillatorBank.h"
#include "VoiceState.h"
#include "VoiceProcessor.h"
#include "VoiceInfo.h"
#include "StereoSample.h"
#include "LFO.h"

class Voice
{
public:

    void prepare(
        double sampleRate);

    void setInstrument(
        const Instrument& instrument);

    void setMidiNote(
        int midiNote);

    // Stage 14 - Portamento. Like setMidiNote(), but instead of
    // jumping to the new note's pitch instantly, glides there
    // from fromFrequency over glideTimeSeconds. Used specifically
    // when VoiceManager has to reuse an already-sounding voice
    // (the pool is full) rather than for ordinary fresh notes -
    // see VoiceManager::noteOn(). If glideTimeSeconds <= 0 or
    // fromFrequency <= 0, this behaves exactly like setMidiNote()
    // (an instant jump), so it's always safe to call.
    void glideToMidiNote(
        int midiNote,
        float fromFrequency,
        float glideTimeSeconds);

    void noteOn();

    void setReleased(bool released);

    bool isReleased() const;

    void setSustained(bool sustained);

    bool isSustained() const;

    void noteOff();

    bool finished() const;
    
    int getMidiNote() const;

    float getFrequency() const;

    // Stage 14 - Portamento. Returns the voice's actual
    // currently-sounding pitch, which may be mid-glide - unlike
    // getFrequency(), which returns the nominal target pitch of
    // the current note. Used by VoiceManager to capture a stolen
    // voice's real pitch as the start point for its next glide,
    // before setInstrument()'s internal reset() clears it.
    float getCurrentFrequency() const;

    void setActive(
        bool active);

    bool isActive() const;

    void setVelocity(
    float velocity);

    float getVelocity() const;

    unsigned long getAge() const;

    void incrementAge();

    void resetAge();

    // Stage 13 - 8-Voice Unison. Assigns this voice's position
    // within a unison stack: index is this voice's 0-based slot,
    // count is the total number of voices spawned for the note
    // (instrument.unisonVoices, clamped). count defaults to 1,
    // meaning "not part of a unison stack" - in that case Voice
    // falls back to Stage 12's plain note-based panning and no
    // extra detune, so nothing changes for existing patches that
    // never set unisonVoices above 1.
    void setUnisonSlot(
        int index,
        int count);

    // Stage 18 - Pitch Bend. value is the normalized bend
    // position in [-1, 1] (standard MIDI-wheel convention: 0 =
    // centered/no bend). Converted to actual semitones using
    // this voice's own instrument.pitchBendRange inside
    // process(), not here - VoiceManager broadcasts the same
    // normalized value to every active voice regardless of which
    // instrument each one is playing, since different patches
    // can have different bend ranges.
    void setPitchBend(
        float value);

    // Stage 19 - Mod Wheel. value is the normalized wheel
    // position in [0, 1] (standard MIDI convention: 0 = wheel at
    // rest). Scales this voice's vibrato depth on top of
    // instrument.vibratoDepth, by instrument.modWheelRange - see
    // process().
    void setModWheel(
        float value);

    void reset();

    StereoSample process();

private:

    // Shared factory for the primary / secondary / sub
    // oscillators, all of which are built from the same
    // WaveType enum.
    static std::unique_ptr<Oscillator>
    createOscillator(
        WaveType type);

    OscillatorBank
        oscillators;

    VoiceProcessor
        processor;

    // Stage 16 - LFO Core. Lives here rather than inside
    // VoiceState deliberately: VoiceState gets fully
    // reconstructed (state = VoiceState{}) on every note-on via
    // reset(), which would silently wipe this LFO's sample-rate
    // configuration every single note if it lived there instead -
    // the same reason oscillators/processor above are also
    // Voice-level members rather than VoiceState members. Its
    // phase resets on note-on only when instrument.vibratoSync is
    // true (see setInstrument()); otherwise it free-runs
    // continuously across notes on this voice.
    LFO
        vibratoLFO;

    // Stage 17 - LFO Matrix / Modulation Routing. A second,
    // independent LFO whose destination is assignable (see
    // Instrument::modLFODestination) rather than fixed to pitch
    // like vibratoLFO above. Same Voice-level-member reasoning
    // applies: it must not live inside VoiceState, or its
    // sample-rate configuration would be silently wiped on every
    // note-on by reset().
    LFO
        modLFO;

    // Stage 18 - Pitch Bend. A Voice-level member (not inside
    // VoiceState) for the same reason as vibratoLFO/modLFO above:
    // it's live performance state, and shouldn't reset to 0 just
    // because this voice slot gets reused for a new note while a
    // bend is being held. VoiceManager::noteOn() also explicitly
    // re-applies the current bend to every newly-triggered voice
    // regardless, so this is defense in depth, not the only thing
    // making that work.
    float pitchBendValue =
        0.0f;

    // Stage 19 - Mod Wheel. Same Voice-level-member reasoning as
    // pitchBendValue above.
    float modWheelValue =
        0.0f;

    VoiceState
        state;

    Instrument
        instrument;

    VoiceInfo
        info;

    int unisonIndex =
        0;

    int unisonCount =
        1;

    double sampleRate =
        44100.0;
};

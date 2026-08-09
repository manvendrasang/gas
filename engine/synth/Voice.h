#pragma once

#include <memory>

#include "Instrument.h"
#include "Oscillator.h"
#include "OscillatorBank.h"
#include "VoiceState.h"
#include "VoiceProcessor.h"
#include "VoiceInfo.h"
#include "StereoSample.h"

class Voice
{
public:

    void prepare(
        double sampleRate);

    void setInstrument(
        const Instrument& instrument);

    void setMidiNote(
        int midiNote);

    void noteOn();

    void setReleased(bool released);

    bool isReleased() const;

    void setSustained(bool sustained);

    bool isSustained() const;

    void noteOff();

    bool finished() const;
    
    int getMidiNote() const;

    float getFrequency() const;

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

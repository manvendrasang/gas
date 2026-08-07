#pragma once

#include <memory>

#include "Instrument.h"
#include "Oscillator.h"
#include "OscillatorBank.h"
#include "VoiceState.h"
#include "VoiceProcessor.h"
#include "VoiceInfo.h"

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

    void reset();

    float process();

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

    double sampleRate =
        44100.0;
};

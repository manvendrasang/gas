#pragma once

#include "Instrument.h"
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
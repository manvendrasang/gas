#pragma once

#include "VoiceManager.h"
#include "VoiceMixer.h"
#include "StereoSample.h"

class SynthEngine
{
public:

    void prepare(
        double sampleRate);

    void noteOn(
        int midiNote,
        float velocity,
        const Instrument& instrument);

    void noteOff(
        int midiNote);

    // Stage 18 - Pitch Bend. value is the normalized bend
    // position in [-1, 1] (0 = centered/no bend).
    void setPitchBend(
        float value);

    // Stage 19 - Mod Wheel. value is the normalized wheel
    // position in [0, 1] (0 = wheel at rest).
    void setModWheel(
        float value);

    StereoSample process();

private:

    VoiceManager
        voiceManager;

    VoiceMixer
        mixer;
};
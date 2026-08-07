#pragma once

#include "VoiceManager.h"
#include "VoiceMixer.h"

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

    float process();

private:

    VoiceManager
        voiceManager;

    VoiceMixer
        mixer;
};
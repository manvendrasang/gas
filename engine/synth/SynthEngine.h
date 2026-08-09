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

    StereoSample process();

private:

    VoiceManager
        voiceManager;

    VoiceMixer
        mixer;
};
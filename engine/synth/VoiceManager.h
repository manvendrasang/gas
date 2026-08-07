#pragma once

#include <vector>

#include "Voice.h"
#include "Instrument.h"
#include "VoiceAllocator.h"

class VoiceManager
{
public:

    explicit VoiceManager(
        int maxVoices = 32);

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

    std::vector<Voice>
        voices;

    VoiceAllocator
        allocator;

    double sampleRate =
        44100.0;
};
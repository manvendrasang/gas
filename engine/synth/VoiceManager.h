#pragma once

#include <vector>

#include "Voice.h"
#include "Instrument.h"
#include "VoiceAllocator.h"
#include "StereoSample.h"

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

    // Stage 18 - Pitch Bend. value is the normalized bend
    // position in [-1, 1]. Unlike Instrument's parameters, this
    // is channel-wide live performance state: it applies
    // immediately to every currently-active voice (whatever
    // they're playing, however they got triggered), and is
    // remembered so any note played afterward starts already
    // bent, matching standard MIDI pitch-wheel behavior.
    void setPitchBend(
        float value);

    // Stage 19 - Mod Wheel. value is the normalized wheel
    // position in [0, 1]. Same real-time, channel-wide broadcast
    // behavior as setPitchBend() above.
    void setModWheel(
        float value);

    StereoSample process();

private:

    std::vector<Voice>
        voices;

    float currentPitchBend =
        0.0f;

    // Stage 19 - Mod Wheel.
    float currentModWheel =
        0.0f;

    double sampleRate =
        44100.0;
};
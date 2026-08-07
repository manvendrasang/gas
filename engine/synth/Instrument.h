#pragma once

#include "ADSR.h"

enum class WaveType
{
    Sine,
    Square,
    Saw,
    Triangle,
    Noise
};

struct Instrument
{
    WaveType waveType =
        WaveType::Square;

    ADSRParameters envelope;

    float frequency = 440.0f;

    float volume = 0.5f;

    float frequencySlide = 0.0f;

    float vibratoDepth = 0.0f;

    float vibratoSpeed = 0.0f;

    float noiseMix = 0.0f;

    // Bfxr

    float squareDuty = 0.5f;

    float dutySweep = 0.0f;

    float pitchJumpAmount = 0.0f;

    float pitchJumpTime = 0.0f;

    float repeatSpeed = 0.0f;

    float repeatTimer = 0.0f;

    float bitCrush = 0.0f;

    float lowpassCutoff = 1.0f;

    float highpassCutoff = 0.0f;

    // Secondary oscillator

    WaveType secondaryWaveType =
        WaveType::Sine;

    float secondaryFrequency =
        440.0f;

    float secondaryVolume =
        0.0f;


    // Sub oscillator

    bool subEnabled =
        false;

    float subVolume =
        0.30f;


    // Unison

    int unisonVoices =
        1;

    float unisonDetune =
        0.0f;


    // Stereo

    float stereoWidth =
        0.0f;
};
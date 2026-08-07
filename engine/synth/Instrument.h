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

    // Secondary oscillator (Stage 11 - Detune / Supersaw Foundation)

    WaveType secondaryWaveType =
        WaveType::Sine;

    // Detune of the secondary oscillator relative to the
    // primary, in cents (100 cents = 1 semitone). The
    // secondary always tracks the voice's current pitch,
    // it is never a fixed absolute frequency.
    float secondaryDetune =
        12.0f;

    float secondaryVolume =
        0.0f;


    // Sub oscillator (Stage 11 - octave tracking)

    bool subEnabled =
        false;

    // Octaves relative to the primary oscillator's current
    // pitch. Negative values sit below the primary (-1 = one
    // octave down). The sub always tracks pitch changes made
    // to the voice, it never drifts to a fixed frequency.
    int subOctaveOffset =
        -1;

    float subVolume =
        0.30f;


    // Unison (foundation - full multi-voice unison lands in
    // a later stage)

    int unisonVoices =
        1;

    float unisonDetune =
        0.0f;


    // Stereo (foundation - stereo spread lands in a later
    // stage)

    float stereoWidth =
        0.0f;
};

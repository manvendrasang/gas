#pragma once

enum class SfxWaveType
{
    Sine,
    Square,
    Saw,
    Triangle,
    Noise
};

struct SfxParameters
{
    SfxWaveType waveType =
        SfxWaveType::Square;

    // Envelope

    float attack = 0.0f;

    float sustain = 0.0f;

    float decay = 0.1f;

    float punch = 0.0f;

    // Pitch

    float frequency = 440.0f;

    float frequencyLimit = 0.0f;

    float frequencySlide = 0.0f;

    float deltaSlide = 0.0f;

    // Vibrato

    float vibratoDepth = 0.0f;

    float vibratoSpeed = 0.0f;

    // Square Wave

    float squareDuty = 0.5f;

    float dutySweep = 0.0f;

    // Filters

    float lowpassCutoff = 1.0f;

    float highpassCutoff = 0.0f;

    // Noise

    float noiseMix = 0.0f;

    // Output

    float volume = 0.5f;

    float pitchJumpAmount = 0.0f;

    float pitchJumpTime = 0.0f;

    float repeatSpeed = 0.0f;

    float bitCrush = 0.0f;
};
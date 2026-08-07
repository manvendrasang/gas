#pragma once

#include "../../engine/synth/Instrument.h"

inline Instrument ExplosionPreset()
{
    Instrument explosion;

    explosion.waveType =
        WaveType::Noise;

    explosion.frequency =
        100.0f;

    explosion.volume =
        0.8f;

    explosion.noiseMix =
        1.0f;

    explosion.envelope.attack =
        0.001f;

    explosion.envelope.decay =
        0.6f;

    explosion.envelope.sustain =
        0.0f;

    explosion.envelope.release =
        0.1f;

    return explosion;
}
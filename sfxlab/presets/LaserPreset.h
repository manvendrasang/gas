#pragma once

#include "../../engine/synth/Instrument.h"

inline Instrument LaserPreset()
{
    Instrument laser;

    laser.waveType =
        WaveType::Square;

    laser.frequency =
        1200.0f;

    laser.frequencySlide =
        -0.4f;

    laser.volume =
        0.6f;

    laser.envelope.attack =
        0.001f;

    laser.envelope.decay =
        0.15f;

    laser.envelope.sustain =
        0.0f;

    laser.envelope.release =
        0.01f;

    return laser;
}
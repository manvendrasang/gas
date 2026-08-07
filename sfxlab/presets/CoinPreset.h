#pragma once

#include "../../engine/synth/Instrument.h"

inline Instrument CoinPreset()
{
    Instrument coin;

    coin.waveType =
        WaveType::Square;

    coin.frequency =
        1200.0f;

    coin.volume =
        0.5f;

    coin.envelope.attack =
        0.001f;

    coin.envelope.decay =
        0.08f;

    coin.envelope.sustain =
        0.0f;

    coin.envelope.release =
        0.02f;

    return coin;
}
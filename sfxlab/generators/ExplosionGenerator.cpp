#include "ExplosionGenerator.h"

#include "../parameters/SfxParameters.h"
#include "../builders/InstrumentBuilder.h"

Instrument ExplosionGenerator::generate()
{
    SfxParameters params;

    params.waveType =
        SfxWaveType::Noise;

    params.noiseMix =
        1.0f;

    params.frequency =
        100.0f;

    params.attack =
        0.001f;

    params.decay =
        0.6f;

    params.volume =
        0.8f;

    return
        InstrumentBuilder::build(
            params);
}
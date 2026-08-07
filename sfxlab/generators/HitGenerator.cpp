#include "HitGenerator.h"

#include "../parameters/SfxParameters.h"
#include "../builders/InstrumentBuilder.h"

Instrument HitGenerator::generate()
{
    SfxParameters params;

    params.waveType =
        SfxWaveType::Noise;

    params.frequency =
        180.0f;

    params.noiseMix =
        1.0f;

    params.attack =
        0.001f;

    params.decay =
        0.12f;

    params.volume =
        0.7f;

    return
        InstrumentBuilder::build(
            params);
}
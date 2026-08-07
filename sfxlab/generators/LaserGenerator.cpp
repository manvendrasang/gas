#include "LaserGenerator.h"

#include "../parameters/SfxParameters.h"
#include "../builders/InstrumentBuilder.h"

Instrument LaserGenerator::generate()
{
    SfxParameters params;

    params.waveType =
        SfxWaveType::Square;

    params.frequency =
        1500.0f;

    params.frequencySlide =
        -0.8f;

    params.squareDuty =
        0.15f;

    params.dutySweep =
        0.002f;

    params.repeatSpeed =
        0.05f;

    params.attack =
        0.001f;

    params.decay =
        0.20f;

    params.volume =
        0.7f;

    return
        InstrumentBuilder::build(
            params);
}
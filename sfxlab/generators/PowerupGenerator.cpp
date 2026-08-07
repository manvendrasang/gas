#include "PowerupGenerator.h"

#include "../parameters/SfxParameters.h"
#include "../builders/InstrumentBuilder.h"

Instrument PowerupGenerator::generate()
{
    SfxParameters params;

    params.waveType =
        SfxWaveType::Square;

    params.frequency =
        600.0f;

    params.frequencySlide =
        0.25f;

    params.squareDuty =
        0.15f;

    params.attack =
        0.001f;

    params.decay =
        0.30f;

    params.volume =
        0.7f;

    return
        InstrumentBuilder::build(
            params);
}
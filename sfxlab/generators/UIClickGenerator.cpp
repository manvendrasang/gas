#include "UIClickGenerator.h"

#include "../parameters/SfxParameters.h"
#include "../builders/InstrumentBuilder.h"

Instrument UIClickGenerator::generate()
{
    SfxParameters params;

    params.waveType =
        SfxWaveType::Square;

    params.frequency =
        1000.0f;

    params.squareDuty =
        0.10f;

    params.attack =
        0.001f;

    params.decay =
        0.04f;

    params.volume =
        0.5f;

    return
        InstrumentBuilder::build(
            params);
}
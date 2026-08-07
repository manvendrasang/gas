#include "CoinGenerator.h"

#include "../parameters/SfxParameters.h"
#include "../builders/InstrumentBuilder.h"

Instrument CoinGenerator::generate()
{
    SfxParameters params;

    params.waveType =
        SfxWaveType::Square;

    params.frequency =
        1800.0f;

    params.frequencySlide =
        0.05f;

    params.squareDuty =
        0.15f;

    params.dutySweep =
        0.0015f;

    params.attack =
        0.001f;

    params.decay =
        0.08f;

    params.volume =
        0.6f;

    return
        InstrumentBuilder::build(
            params);
}
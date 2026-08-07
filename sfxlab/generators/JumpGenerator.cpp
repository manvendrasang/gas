#include "JumpGenerator.h"

#include "../parameters/SfxParameters.h"
#include "../builders/InstrumentBuilder.h"

Instrument JumpGenerator::generate()
{
    SfxParameters params;

    params.waveType =
        SfxWaveType::Sine;

    params.frequency =
        440.0f;

    params.attack =
        0.01f;

    params.decay =
        0.5f;

    params.volume =
        1.0f;

    return
        InstrumentBuilder::build(
            params);
}
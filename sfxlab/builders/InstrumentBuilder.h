#pragma once

#include "../../engine/synth/Instrument.h"

#include "../parameters/SfxParameters.h"

class InstrumentBuilder
{
public:

    static Instrument
    build(
        const SfxParameters& params);
};
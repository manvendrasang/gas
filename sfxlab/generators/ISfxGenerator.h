#pragma once

#include "../../engine/synth/Instrument.h"

class ISfxGenerator
{
public:

    virtual ~ISfxGenerator() = default;

    virtual Instrument
    generate() = 0;
};
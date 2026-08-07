#pragma once

#include "ISfxGenerator.h"

class PowerupGenerator :
    public ISfxGenerator
{
public:

    Instrument generate() override;
};
#pragma once

#include "ISfxGenerator.h"

class ExplosionGenerator :
    public ISfxGenerator
{
public:

    Instrument generate() override;
};
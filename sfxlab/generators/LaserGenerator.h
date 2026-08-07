#pragma once

#include "ISfxGenerator.h"

class LaserGenerator :
    public ISfxGenerator
{
public:

    Instrument generate() override;
};
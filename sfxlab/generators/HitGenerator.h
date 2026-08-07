#pragma once

#include "ISfxGenerator.h"

class HitGenerator :
    public ISfxGenerator
{
public:

    Instrument generate() override;
};
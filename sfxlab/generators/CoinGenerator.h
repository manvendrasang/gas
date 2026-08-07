#pragma once

#include "ISfxGenerator.h"

class CoinGenerator :
    public ISfxGenerator
{
public:

    Instrument generate() override;
};
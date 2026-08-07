#pragma once

#include "ISfxGenerator.h"

class UIClickGenerator :
    public ISfxGenerator
{
public:

    Instrument generate() override;
};
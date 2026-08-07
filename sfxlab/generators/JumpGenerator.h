#pragma once

#include "ISfxGenerator.h"

class JumpGenerator :
    public ISfxGenerator
{
public:

    Instrument generate() override;
};
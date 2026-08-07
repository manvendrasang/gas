#pragma once

#include <memory>

#include "generators/ISfxGenerator.h"

enum class SfxType
{
    Coin,
    Laser,
    Explosion,
    Jump,
    Powerup,
    Hit,
    UIClick
};

class SfxFactory
{
public:

    static std::unique_ptr<ISfxGenerator>
    create(
        SfxType type);
};
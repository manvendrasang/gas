#include "SfxFactory.h"

#include "generators/CoinGenerator.h"
#include "generators/LaserGenerator.h"
#include "generators/ExplosionGenerator.h"

#include "generators/JumpGenerator.h"
#include "generators/PowerupGenerator.h"
#include "generators/HitGenerator.h"
#include "generators/UIClickGenerator.h"

std::unique_ptr<ISfxGenerator>
SfxFactory::create(
    SfxType type)
{
    switch(type)
    {
        case SfxType::Coin:
            return
                std::make_unique<CoinGenerator>();

        case SfxType::Laser:
            return
                std::make_unique<LaserGenerator>();

        case SfxType::Explosion:
            return
                std::make_unique<ExplosionGenerator>();

        case SfxType::Jump:
            return
                std::make_unique<JumpGenerator>();

        case SfxType::Powerup:
            return
                std::make_unique<PowerupGenerator>();

        case SfxType::Hit:
            return
                std::make_unique<HitGenerator>();

        case SfxType::UIClick:
            return
                std::make_unique<UIClickGenerator>();
    }

    return nullptr;
}
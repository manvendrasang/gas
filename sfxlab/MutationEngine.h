#pragma once

#include "../engine/synth/Instrument.h"

#include <vector>

class MutationEngine
{
public:

    std::vector<Instrument>
    generateVariations(
        const Instrument& base,
        int count);

private:

    float randomRange(
        float min,
        float max);
};
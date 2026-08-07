#pragma once

#include <vector>

#include "Instrument.h"

class AudioRenderer
{
public:

    std::vector<float>
    render(
        const Instrument& instrument,
        float durationSeconds);
};
#pragma once

#include "../../sfxlab/parameters/SfxParameters.h"

class ParameterEditor
{
public:

    void setParameters(
        const SfxParameters& params);

    SfxParameters&
    getParameters();

    void setFrequency(
        float frequency);

    void setDecay(
        float decay);

    void setSlide(
        float slide);

    void setDutyCycle(
        float duty);

    void setDutySweep(
        float sweep);

private:

    SfxParameters parameters;
};
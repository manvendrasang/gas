#include "ParameterEditor.h"

void ParameterEditor::setParameters(
    const SfxParameters& params)
{
    parameters = params;
}

SfxParameters&
ParameterEditor::getParameters()
{
    return parameters;
}

void ParameterEditor::setFrequency(
    float frequency)
{
    parameters.frequency =
        frequency;
}

void ParameterEditor::setDecay(
    float decay)
{
    parameters.decay =
        decay;
}

void ParameterEditor::setSlide(
    float slide)
{
    parameters.frequencySlide =
        slide;
}

void ParameterEditor::setDutyCycle(
    float duty)
{
    parameters.squareDuty =
        duty;
}

void ParameterEditor::setDutySweep(
    float sweep)
{
    parameters.dutySweep =
        sweep;
}
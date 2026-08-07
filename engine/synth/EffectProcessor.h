#pragma once

class EffectProcessor
{
public:

    void setBitCrush(
        float amount)
    {
        bitCrush =
            amount;

        counter = 0.0f;

        heldSample = 0.0f;
    }

    float process(
        float sample)
    {
        if (bitCrush <= 0.0f)
            return sample;

        counter++;

        if (counter >= bitCrush)
        {
            counter = 0.0f;
            heldSample = sample;
        }

        return heldSample;
    }

private:

    float bitCrush =
        0.0f;

    float counter =
        0.0f;

    float heldSample =
        0.0f;
};
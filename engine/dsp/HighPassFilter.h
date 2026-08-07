#pragma once

class HighPassFilter
{
public:

    void setCutoff(
        float cutoff)
    {
        if (cutoff <= 0.0f)
        {
            enabled = false;
            return;
        }

        enabled = true;

        alpha = cutoff;
    }

    float process(
        float sample)
    {
        if (!enabled)
            return sample;

        float output =
            alpha *
            (
                previousOutput +
                sample -
                previousInput
            );

        previousInput =
            sample;

        previousOutput =
            output;

        return output;
    }

private:

    bool enabled =
        false;

    float alpha =
        0.5f;

    float previousInput =
        0.0f;

    float previousOutput =
        0.0f;
};
#pragma once

class LowPassFilter
{
public:

    void setCutoff(
        float cutoff)
    {
        alpha = cutoff;
    }

    float process(
        float sample)
    {
        previous =
            previous +
            alpha *
            (sample - previous);

        return previous;
    }

private:

    float previous = 0.0f;

    float alpha = 1.0f;
};
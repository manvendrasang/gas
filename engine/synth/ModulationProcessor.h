#pragma once

#include <cmath>

class ModulationProcessor
{
public:

    void prepare(
        double sr)
    {
        sampleRate = sr;
    }

    void reset()
    {
        phase = 0.0f;
    }

    float applyVibrato(
        float frequency,
        float depth,
        float speed)
    {
        if (depth <= 0.0f ||
            speed <= 0.0f)
        {
            return frequency;
        }

        phase +=
            (2.0f * 3.14159265f * speed)
            /
            static_cast<float>(sampleRate);

        if (phase >=
            2.0f * 3.14159265f)
        {
            phase -=
                2.0f * 3.14159265f;
        }

        return
            frequency +
            std::sin(phase) * depth;
    }

private:

    double sampleRate =
        44100.0;

    float phase =
        0.0f;
};
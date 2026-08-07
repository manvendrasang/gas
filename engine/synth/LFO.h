#pragma once

#include <cmath>

class LFO
{
public:

    void prepare(
        double sampleRate)
    {
        this->sampleRate =
            sampleRate;
    }

    void setFrequency(
        float frequency)
    {
        this->frequency =
            frequency;
    }

    void setDepth(
        float depth)
    {
        this->depth =
            depth;
    }

    void reset()
    {
        phase = 0.0f;
    }

    float process()
    {
        float output =
            std::sin(phase) *
            depth;

        phase +=
            (2.0f * 3.14159265358979323846f *
             frequency)
            /
            static_cast<float>(
                sampleRate);

        if (phase >
            2.0f * 3.14159265358979323846f)
        {
            phase -=
                2.0f * 3.14159265358979323846f;
        }

        return output;
    }

private:

    double sampleRate =
        44100.0;

    float frequency =
        5.0f;

    float depth =
        0.0f;

    float phase =
        0.0f;
};
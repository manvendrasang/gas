#pragma once

#include "../Oscillator.h"
#include <random>

class NoiseOscillator : public Oscillator
{
public:

    void prepare(double) override
    {
    }

    void setFrequency(float) override
    {
    }

    float process() override
    {
        return distribution(generator);
    }

    void reset() override
    {
    }

private:

    std::mt19937 generator
    {
        std::random_device{}()
    };

    std::uniform_real_distribution<float>
        distribution{-1.0f, 1.0f};
};
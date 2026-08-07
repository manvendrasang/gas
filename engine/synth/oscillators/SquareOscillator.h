#pragma once

#include "../Oscillator.h"

class SquareOscillator :
    public Oscillator
{
public:

    void prepare(
        double sr) override
    {
        sampleRate = sr;
    }

    void setFrequency(
        float freq) override
    {
        frequency = freq;
    }

    void setDutyCycle(
        float duty) override
    {
        dutyCycle = duty;
    }

    float process() override
    {
        phase +=
            frequency /
            sampleRate;

        while (phase >= 1.0)
            phase -= 1.0;

        return
            phase < dutyCycle
            ? 1.0f
            : -1.0f;
    }

private:

    float frequency = 440.0f;

    double sampleRate = 44100.0;

    double phase = 0.0;

    float dutyCycle = 0.5f;
};
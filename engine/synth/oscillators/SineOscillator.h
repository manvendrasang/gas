#pragma once

#include "../Oscillator.h"
#include <cmath>
#include "../Constants.h"
class SineOscillator : public Oscillator
{
public:

    void prepare(double sampleRate) override
    {
        mSampleRate = sampleRate;
    }

    void setFrequency(float frequency) override
    {
        mFrequency = frequency;
    }

    float process() override
    {
        float sample =
            std::sin(mPhase);

        mPhase +=
            (2.0 * PI * mFrequency)
            / mSampleRate;

        if (mPhase >= 2.0 * PI)
            mPhase -= 2.0 * PI;

        return sample;
    }

    void reset() override
    {
        mPhase = 0.0;
    }

private:

    double mSampleRate = 44100.0;

    float mFrequency = 440.0f;

    double mPhase = 0.0;
};
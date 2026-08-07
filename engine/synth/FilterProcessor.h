#pragma once

#include "../dsp/LowPassFilter.h"
#include "../dsp/HighPassFilter.h"

class FilterProcessor
{
public:

    void setLowpass(
        float cutoff)
    {
        lowpass.setCutoff(cutoff);
    }

    void setHighpass(
        float cutoff)
    {
        highpass.setCutoff(cutoff);
    }

    float process(
        float sample)
    {
        sample =
            lowpass.process(sample);

        sample =
            highpass.process(sample);

        return sample;
    }

private:

    LowPassFilter lowpass;

    HighPassFilter highpass;
};
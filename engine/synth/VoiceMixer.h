#pragma once

#include "StereoSample.h"

class VoiceMixer
{
public:

    void setMasterGain(
        float gain)
    {
        masterGain = gain;
    }

    void setLimiter(
        float value)
    {
        limiter = value;
    }

    StereoSample process(
        StereoSample sample)
    {
        sample.left *=
            masterGain;

        sample.right *=
            masterGain;

        sample.left =
            clamp(
                sample.left);

        sample.right =
            clamp(
                sample.right);

        return sample;
    }

private:

    float clamp(
        float value)
    {
        if (value > limiter)
            return limiter;

        if (value < -limiter)
            return -limiter;

        return value;
    }

    float masterGain =
        1.0f;

    float limiter =
        1.0f;
};

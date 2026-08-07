#pragma once

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

    float process(
        float sample)
    {
        sample *=
            masterGain;

        if (sample > limiter)
            sample = limiter;

        if (sample < -limiter)
            sample = -limiter;

        return sample;
    }

private:

    float masterGain =
        1.0f;

    float limiter =
        1.0f;
};
#pragma once

#include <memory>

#include "Oscillator.h"

class OscillatorBank
{
public:

    void prepare(double sampleRate);

    void setPrimary(std::unique_ptr<Oscillator> osc);

    void setSecondary(std::unique_ptr<Oscillator> osc);

    void setNoise(std::unique_ptr<Oscillator> osc);

    void setSub(std::unique_ptr<Oscillator> osc);

    void setPrimaryFrequency(float frequency);

    void setSecondaryFrequency(float frequency);

    void setSubFrequency(float frequency);

    void setDutyCycle(float duty);

    void setPrimaryGain(float gain);

    void setSecondaryGain(float gain);

    void setNoiseGain(float gain);

    void setSubGain(float gain);

    void reset();

    float process();

private:

    // Stable gain staging: returns a normalization factor so that
    // stacking the secondary / sub / noise oscillators on top of
    // the primary can never make a voice louder than a primary-only
    // voice at the same gain. When the combined gain of the active
    // oscillators is at or below unity, the factor is 1.0 and every
    // existing single-oscillator patch is completely unaffected.
    float gainStagingNormalization() const;

    double sampleRate = 44100.0;

    std::unique_ptr<Oscillator> primary;

    std::unique_ptr<Oscillator> secondary;

    std::unique_ptr<Oscillator> noise;

    std::unique_ptr<Oscillator> sub;

    float primaryGain = 1.0f;

    float secondaryGain = 0.0f;

    float noiseGain = 0.0f;

    float subGain = 0.0f;
};

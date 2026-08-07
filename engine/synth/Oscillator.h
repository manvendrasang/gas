#pragma once

class Oscillator
{
public:

    virtual ~Oscillator() = default;

    virtual void prepare(
        double sampleRate) = 0;

    virtual void setFrequency(
        float frequency) = 0;

    virtual void setDutyCycle(
        float duty)
    {
        // Default implementation.
        // Only SquareOscillator uses this.
    }

    virtual void reset()
    {
        // Default implementation.
        // Oscillators can override if needed.
    }

    virtual float process() = 0;
};
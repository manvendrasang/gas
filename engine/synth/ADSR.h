#pragma once

struct ADSRParameters
{
    float attack  = 0.01f;
    float decay   = 0.10f;
    float sustain = 0.80f;
    float release = 0.20f;
};

class ADSR
{
public:

    void prepare(double sampleRate);

    void setParameters(
        const ADSRParameters& params);

    void noteOn();

    void noteOff();

    float process();

    bool isActive() const;

private:

    enum class State
    {
        Idle,
        Attack,
        Decay,
        Sustain,
        Release
    };

    State state = State::Idle;

    ADSRParameters parameters;

    double sampleRate = 44100.0;

    float level = 0.0f;
};
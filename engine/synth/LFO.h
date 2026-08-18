#pragma once

#include <cmath>

// Stage 16 - LFO Core.
enum class LFOShape
{
    Sine,
    Triangle,
    Square,
    Saw
};

// Stage 17 - LFO Matrix / Modulation Routing.
enum class ModDestination
{
    None,
    Pitch,
    Volume,
    Filter,
    Pan
};

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

    // Stage 16 - LFO Core.
    void setShape(
        LFOShape shape)
    {
        this->shape =
            shape;
    }

    void reset()
    {
        phase = 0.0f;
    }

    float process()
    {
        const float output =
            waveform() *
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

    // Stage 16 - LFO Core. Returns -1..1 for the currently
    // selected shape, evaluated at the current phase. Sine keeps
    // the original std::sin() call exactly as before (no change
    // to existing math); the other three are computed from a
    // normalized 0..1 phase fraction.
    float waveform() const
    {
        constexpr float twoPi =
            2.0f * 3.14159265358979323846f;

        switch (shape)
        {
            case LFOShape::Sine:
                return
                    std::sin(phase);

            case LFOShape::Triangle:
            {
                const float t =
                    phase / twoPi;

                return
                    (t < 0.5f)
                    ? (4.0f * t - 1.0f)
                    : (3.0f - 4.0f * t);
            }

            case LFOShape::Square:
            {
                const float t =
                    phase / twoPi;

                return
                    (t < 0.5f) ? 1.0f : -1.0f;
            }

            case LFOShape::Saw:
            {
                const float t =
                    phase / twoPi;

                return
                    2.0f * t - 1.0f;
            }
        }

        return
            std::sin(phase);
    }

    double sampleRate =
        44100.0;

    float frequency =
        5.0f;

    float depth =
        0.0f;

    float phase =
        0.0f;

    LFOShape shape =
        LFOShape::Sine;
};

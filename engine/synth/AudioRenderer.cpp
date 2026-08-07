#include "AudioRenderer.h"

#include "SynthEngine.h"

std::vector<float>
AudioRenderer::render(
    const Instrument& instrument,
    float durationSeconds)
{
    constexpr int sampleRate =
        44100;

    const int totalSamples =
        static_cast<int>(
            durationSeconds *
            sampleRate);

    std::vector<float>
        buffer;

    buffer.reserve(
        totalSamples);

    SynthEngine
        engine;

    engine.prepare(
        sampleRate);

    engine.noteOn(
    69,
    1.0f,
    instrument);

    for (int i = 0;
         i < totalSamples;
         i++)
    {
        buffer.push_back(
            engine.process());
    }

    return buffer;
}
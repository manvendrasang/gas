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

    // Stage 12 - Stereo Spread. The buffer is interleaved
    // stereo (L, R, L, R, ...): two floats per sample frame.
    // WaveExporter and AudioPlayer both treat this vector as a
    // flat sequence of samples already, so this is the only
    // place that needs to know the frame/channel distinction.
    std::vector<float>
        buffer;

    buffer.reserve(
        totalSamples * 2);

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
        StereoSample frame =
            engine.process();

        buffer.push_back(
            frame.left);

        buffer.push_back(
            frame.right);
    }

    return buffer;
}
#include "WaveExporter.h"

#include <fstream>
#include <cstdint>

bool WaveExporter::write(
    const std::string& path,
    const std::vector<float>& samples)
{
    std::ofstream file(
        path,
        std::ios::binary);

    if(!file)
        return false;

    const int sampleRate =
        44100;

    const int bitsPerSample =
        16;

    // Stage 12 - Stereo Spread. AudioRenderer now produces
    // interleaved stereo (L, R, L, R, ...), so this writer emits
    // a 2-channel WAV. The sample-writing loop below is
    // unchanged: it just walks the vector in order regardless of
    // channel count, which is already correct for interleaved
    // data.
    const int channels =
        2;

    uint32_t dataSize =
        samples.size()
        *
        sizeof(int16_t);

    file.write("RIFF",4);

    uint32_t chunkSize =
        36 + dataSize;

    file.write(
        reinterpret_cast<char*>(
            &chunkSize),
        4);

    file.write("WAVE",4);

    file.write("fmt ",4);

    uint32_t subchunk1 = 16;

    file.write(
        reinterpret_cast<char*>(
            &subchunk1),
        4);

    uint16_t format = 1;

    file.write(
        reinterpret_cast<char*>(
            &format),
        2);

    uint16_t numChannels =
        channels;

    file.write(
        reinterpret_cast<char*>(
            &numChannels),
        2);

    file.write(
        reinterpret_cast<const char*>(
            &sampleRate),
        4);

    uint32_t byteRate =
        sampleRate
        *
        channels
        *
        bitsPerSample
        / 8;

    file.write(
        reinterpret_cast<char*>(
            &byteRate),
        4);

    uint16_t blockAlign =
        channels
        *
        bitsPerSample
        / 8;

    file.write(
        reinterpret_cast<char*>(
            &blockAlign),
        2);

    uint16_t bps =
        bitsPerSample;

    file.write(
        reinterpret_cast<char*>(
            &bps),
        2);

    file.write("data",4);

    file.write(
        reinterpret_cast<char*>(
            &dataSize),
        4);

    for(float sample : samples)
    {
        int16_t pcm =
            static_cast<int16_t>(
                sample * 32767);

        file.write(
            reinterpret_cast<char*>(
                &pcm),
            sizeof(int16_t));
    }

    return true;
}
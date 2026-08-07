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

    const int channels =
        1;

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
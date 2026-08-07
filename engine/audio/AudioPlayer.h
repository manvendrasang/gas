#pragma once

#include <vector>

#include "../../thirdparty/miniaudio.h"

class AudioPlayer
{
public:

    bool initialize();

    void shutdown();

    void play(
        const std::vector<float>& samples);

private:

    static void dataCallback(
        ma_device* device,
        void* output,
        const void* input,
        ma_uint32 frameCount);

    ma_device device;

    std::vector<float>
        playbackBuffer;

    size_t playbackPosition = 0;

    bool initialized = false;
};
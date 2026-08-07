#include "AudioPlayer.h"

#include <cstring>

bool AudioPlayer::initialize()
{
    ma_device_config config =
        ma_device_config_init(
            ma_device_type_playback);

    config.playback.format =
        ma_format_f32;

    config.playback.channels =
        1;

    config.sampleRate =
        44100;

    config.dataCallback =
        dataCallback;

    config.pUserData =
        this;

    if (
        ma_device_init(
            nullptr,
            &config,
            &device)
        != MA_SUCCESS)
    {
        return false;
    }

    if (
        ma_device_start(
            &device)
        != MA_SUCCESS)
    {
        ma_device_uninit(
            &device);

        return false;
    }

    initialized = true;

    return true;
}

void AudioPlayer::shutdown()
{
    if (!initialized)
        return;

    ma_device_uninit(
        &device);

    initialized = false;
}

void AudioPlayer::play(
    const std::vector<float>& samples)
{
    playbackBuffer =
        samples;

    playbackPosition =
        0;
}

void AudioPlayer::dataCallback(
    ma_device* device,
    void* output,
    const void*,
    ma_uint32 frameCount)
{
    auto* player =
        static_cast<AudioPlayer*>(
            device->pUserData);

    float* out =
        static_cast<float*>(
            output);

    for (
        ma_uint32 i = 0;
        i < frameCount;
        ++i)
    {
        if (
            player->playbackPosition <
            player->playbackBuffer.size())
        {
            out[i] =
                player
                ->playbackBuffer[
                    player
                    ->playbackPosition++];
        }
        else
        {
            out[i] =
                0.0f;
        }
    }
}
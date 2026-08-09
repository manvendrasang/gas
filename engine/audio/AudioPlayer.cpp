#include "AudioPlayer.h"

#include <cstring>

bool AudioPlayer::initialize()
{
    ma_device_config config =
        ma_device_config_init(
            ma_device_type_playback);

    config.playback.format =
        ma_format_f32;

    // Stage 12 - Stereo Spread. The renderer now produces
    // interleaved stereo (L, R, L, R, ...), so playback is opened
    // as 2-channel to match.
    config.playback.channels =
        2;

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

    // Stage 12 - Stereo Spread. playbackBuffer is interleaved
    // stereo (L, R, L, R, ...), matching the 2-channel device
    // opened in initialize(), so the callback must fill
    // frameCount * channels samples rather than frameCount.
    const ma_uint32 sampleCount =
        frameCount *
        device->playback.channels;

    for (
        ma_uint32 i = 0;
        i < sampleCount;
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
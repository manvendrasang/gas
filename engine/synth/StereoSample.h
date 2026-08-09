#pragma once

// A single stereo sample pair. Carried from Voice::process() all
// the way up through VoiceManager, VoiceMixer and SynthEngine so
// that per-voice stereo positioning (Stage 12 - Stereo Spread) can
// reach the audio output without an intermediate mono downmix.
struct StereoSample
{
    float left = 0.0f;

    float right = 0.0f;

    StereoSample& operator+=(
        const StereoSample& other)
    {
        left += other.left;

        right += other.right;

        return *this;
    }
};

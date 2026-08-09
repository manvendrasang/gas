#pragma once

#include <algorithm>
#include <cmath>

#include "Constants.h"
#include "StereoSample.h"

// Stage 12 - Stereo Spread.
//
// This is a foundation, not the final spread engine: it panns
// each *voice* across the stereo field based on how far its note
// sits from a central reference pitch, scaled by the instrument's
// stereoWidth. That is enough to make chords and multi-note
// playback audibly widen when stereoWidth is turned up, without
// requiring multi-voice unison to exist yet.
//
// Once Stage 13 (8-Voice Unison) lands, each unison voice within
// a single note will get its own pan offset instead of - or in
// addition to - the note-based offset computed here.
namespace StereoPanner
{
    // Bipolar pan position in [-1, 1] for a voice, derived from
    // its MIDI note and the instrument's stereoWidth (0 = mono,
    // 1 = full spread).
    inline float computePan(
        int midiNote,
        float stereoWidth)
    {
        constexpr int referenceNote =
            60; // Middle C

        constexpr float spreadRange =
            24.0f; // +/- two octaves reaches the hard edges

        float normalized =
            static_cast<float>(
                midiNote - referenceNote) /
            spreadRange;

        normalized =
            std::clamp(
                normalized,
                -1.0f,
                1.0f);

        const float width =
            std::clamp(
                stereoWidth,
                0.0f,
                1.0f);

        return
            normalized * width;
    }

    // Splits a mono sample into an equal-power stereo pair for a
    // bipolar pan position in [-1, 1]. Equal-power (as opposed to
    // a linear crossfade) keeps combined left/right energy
    // constant across the field instead of dipping in the
    // center, which is what a linear pan law would do.
    inline StereoSample pan(
        float sample,
        float panPosition)
    {
        panPosition =
            std::clamp(
                panPosition,
                -1.0f,
                1.0f);

        const float angle =
            (panPosition + 1.0f) *
            (static_cast<float>(PI) / 4.0f);

        StereoSample result;

        result.left =
            sample * std::cos(angle);

        result.right =
            sample * std::sin(angle);

        return result;
    }
}

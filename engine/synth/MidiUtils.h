#pragma once

#include <string>

namespace MidiUtils
{
    constexpr int MiddleC = 60;

    constexpr int A4Note = 69;

    constexpr float A4Frequency = 440.0f;

    float noteToFrequency(
        int midiNote);

    int octave(
        int midiNote);

    std::string noteName(
        int midiNote);
}
#include "MidiUtils.h"

#include <cmath>

namespace
{
    constexpr const char* names[12] =
    {
        "C",
        "C#",
        "D",
        "D#",
        "E",
        "F",
        "F#",
        "G",
        "G#",
        "A",
        "A#",
        "B"
    };
}

float MidiUtils::noteToFrequency(
    int midiNote)
{
    return
        A4Frequency *
        std::pow(
            2.0f,
            (midiNote - A4Note) / 12.0f);
}

int MidiUtils::octave(
    int midiNote)
{
    return
        (midiNote / 12) - 1;
}

std::string MidiUtils::noteName(
    int midiNote)
{
    return
        std::string(
            names[midiNote % 12]) +
        std::to_string(
            octave(
                midiNote));
}
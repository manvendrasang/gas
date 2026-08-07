#pragma once

#include <string>

namespace MidiUtils
{
    constexpr int MiddleC = 60;

    constexpr int A4Note = 69;

    constexpr float A4Frequency = 440.0f;

    float noteToFrequency(
        int midiNote);

    // Converts an offset in cents (100 cents = 1 semitone)
    // into a frequency multiplier. Used to derive detuned /
    // octave-tracking oscillator frequencies from a base pitch
    // without losing note tracking (e.g. secondary oscillator
    // detune, sub oscillator octave offset).
    float centsToRatio(
        float cents);

    int octave(
        int midiNote);

    std::string noteName(
        int midiNote);
}
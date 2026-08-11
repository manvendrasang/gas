#pragma once

#include "ADSR.h"
#include "LFO.h"

enum class WaveType
{
    Sine,
    Square,
    Saw,
    Triangle,
    Noise
};

struct Instrument
{
    WaveType waveType =
        WaveType::Square;

    ADSRParameters envelope;

    float frequency = 440.0f;

    float volume = 0.5f;

    float frequencySlide = 0.0f;

    float vibratoDepth = 0.0f;

    float vibratoSpeed = 0.0f;

    // Stage 16 - LFO Core. vibratoDepth/vibratoSpeed existed
    // since before Stage 11 but were never actually wired into
    // the signal path (VoiceProcessor::process() accepted them
    // as parameters and silently ignored both) - this stage
    // finally implements real vibrato, using these two alongside
    // the fields below.
    LFOShape vibratoShape = LFOShape::Sine;

    // Whether the vibrato LFO's phase resets to 0 at the start
    // of every note (true, the default - gives every note the
    // same, predictable vibrato onset) or keeps running
    // continuously across notes on the same voice (false - a
    // more chorus-like effect where different notes catch the
    // LFO at different points in its cycle).
    bool vibratoSync = true;

    float noiseMix = 0.0f;

    // Bfxr

    float squareDuty = 0.5f;

    float dutySweep = 0.0f;

    float pitchJumpAmount = 0.0f;

    float pitchJumpTime = 0.0f;

    float repeatSpeed = 0.0f;

    float repeatTimer = 0.0f;

    float bitCrush = 0.0f;

    float lowpassCutoff = 1.0f;

    float highpassCutoff = 0.0f;

    // Secondary oscillator (Stage 11 - Detune / Supersaw Foundation)

    WaveType secondaryWaveType =
        WaveType::Sine;

    // Detune of the secondary oscillator relative to the
    // primary, in cents (100 cents = 1 semitone). The
    // secondary always tracks the voice's current pitch,
    // it is never a fixed absolute frequency.
    float secondaryDetune =
        12.0f;

    float secondaryVolume =
        0.0f;


    // Sub oscillator (Stage 11 - octave tracking)

    bool subEnabled =
        false;

    // Octaves relative to the primary oscillator's current
    // pitch. Negative values sit below the primary (-1 = one
    // octave down). The sub always tracks pitch changes made
    // to the voice, it never drifts to a fixed frequency.
    int subOctaveOffset =
        -1;

    float subVolume =
        0.30f;


    // Unison (Stage 13 - full multi-voice unison)

    int unisonVoices =
        1;

    float unisonDetune =
        0.0f;


    // Stereo (foundation - stereo spread lands in a later
    // stage)

    float stereoWidth =
        0.0f;


    // Portamento (Stage 14). Applies only when a note has to
    // reuse an already-sounding voice because the voice pool is
    // full (a "stolen" voice) - see VoiceManager::noteOn(). In
    // that situation the reused voice's pitch glides from
    // wherever it currently was to the new note over this many
    // seconds, instead of jumping instantly. 0 = off (instant
    // jump, today's behavior). This does not yet cover true
    // monophonic-style portamento on ordinary note retriggers -
    // that lands with Stage 21 (Legato Mode), which will reuse
    // this same glide mechanism.
    float portamentoTime =
        0.0f;
};

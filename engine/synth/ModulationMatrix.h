#pragma once

#include "LFO.h"
#include "EnvelopeGenerator.h"

struct ModulationMatrix
{
    float pitch = 0.0f;

    float volume = 1.0f;

    float pan = 0.0f;

    float filter = 0.0f;

    float pulseWidth = 0.5f;

    LFO vibrato;

    LFO tremolo;

    LFO filterLFO;

    EnvelopeGenerator ampEnvelope;

    EnvelopeGenerator filterEnvelope;

    EnvelopeGenerator pitchEnvelope;

    void reset()
    {
        pitch = 0.0f;
        volume = 1.0f;
        pan = 0.0f;
        filter = 0.0f;
        pulseWidth = 0.5f;

        vibrato.reset();
        tremolo.reset();
        filterLFO.reset();
    }
};
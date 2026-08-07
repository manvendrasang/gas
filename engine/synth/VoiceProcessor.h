#pragma once

#include "VoiceState.h"
#include "ModulationProcessor.h"
#include "FilterProcessor.h"
#include "EffectProcessor.h"
#include "EnvelopeProcessor.h"

class VoiceProcessor
{
public:

    void prepare(
        double sampleRate)
    {
        modulation.prepare(sampleRate);

        envelope.prepare(sampleRate);
    }

    void setEnvelope(
        const ADSRParameters& params)
    {
        envelope.setParameters(params);
    }

    void noteOn()
    {
        envelope.noteOn();
    }

    void noteOff()
    {
        envelope.noteOff();
    }

    bool isActive() const
    {
        return envelope.isActive();
    }

    void setFilters(
        float lowpass,
        float highpass)
    {
        filters.setLowpass(lowpass);

        filters.setHighpass(highpass);
    }

    void setBitCrush(
        float amount)
    {
        effects.setBitCrush(amount);
    }

    float process(
        VoiceState& state,
        float sample,
        float vibratoDepth,
        float vibratoSpeed)
    {
        sample =
            filters.process(sample);

        sample =
            effects.process(sample);

        sample *=
            envelope.process();

        return sample;
    }

private:

    ModulationProcessor
        modulation;

    FilterProcessor
        filters;

    EffectProcessor
        effects;

    EnvelopeProcessor
        envelope;
};
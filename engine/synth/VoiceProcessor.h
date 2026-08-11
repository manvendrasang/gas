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

    // Stage 16 - LFO Core. Previously took VoiceState& and
    // vibratoDepth/vibratoSpeed parameters that were accepted
    // but never used anywhere in this function - real vibrato is
    // now implemented in Voice::process() instead (it has to
    // modulate the oscillator's frequency before the sample is
    // generated, which is earlier than this function ever sees
    // it - by the time a sample reaches here, its pitch has
    // already been baked in). Filters/effects/envelope never
    // touched those parameters either, so dropping them from the
    // signature has no effect on what this function actually
    // does.
    float process(
        float sample)
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

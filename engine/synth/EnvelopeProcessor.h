#pragma once

#include "ADSR.h"

class EnvelopeProcessor
{
public:

    void prepare(
        double sampleRate)
    {
        envelope.prepare(sampleRate);
    }

    void setParameters(
        const ADSRParameters& parameters)
    {
        envelope.setParameters(parameters);
    }

    void noteOn()
    {
        envelope.noteOn();
    }

    void noteOff()
    {
        envelope.noteOff();
    }

    float process()
    {
        return envelope.process();
    }

    bool isActive() const
    {
        return envelope.isActive();
    }

private:

    ADSR envelope;
};
#include "ADSR.h"

void ADSR::prepare(double sr)
{
    sampleRate = sr;
}

void ADSR::setParameters(
    const ADSRParameters& params)
{
    parameters = params;
}

void ADSR::noteOn()
{
    state = State::Attack;
}

void ADSR::noteOff()
{
    state = State::Release;
}

bool ADSR::isActive() const
{
    return state != State::Idle;
}

float ADSR::process()
{
    switch(state)
    {
        case State::Idle:
            return 0.0f;

        case State::Attack:
        {
            level +=
                1.0f /
                (parameters.attack *
                 sampleRate);

            if(level >= 1.0f)
            {
                level = 1.0f;
                state = State::Decay;
            }

            break;
        }

        case State::Decay:
        {
            level -=
                (1.0f -
                 parameters.sustain)
                /
                (parameters.decay *
                 sampleRate);

            if(level <=
               parameters.sustain)
            {
                level =
                    parameters.sustain;

                state =
                    State::Sustain;
            }

            break;
        }

        case State::Sustain:
            break;

        case State::Release:
        {
            level -=
                parameters.sustain
                /
                (parameters.release *
                 sampleRate);

            if(level <= 0.0f)
            {
                level = 0.0f;
                state = State::Idle;
            }

            break;
        }
    }

    return level;
}
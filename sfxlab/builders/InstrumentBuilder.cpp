#include "InstrumentBuilder.h"

Instrument InstrumentBuilder::build(
    const SfxParameters& params)
{
    Instrument instrument;

    switch(params.waveType)
    {
        case SfxWaveType::Sine:
            instrument.waveType =
                WaveType::Sine;
            break;

        case SfxWaveType::Square:
            instrument.waveType =
                WaveType::Square;
            break;

        case SfxWaveType::Saw:
            instrument.waveType =
                WaveType::Saw;
            break;

        case SfxWaveType::Triangle:
            instrument.waveType =
                WaveType::Triangle;
            break;

        case SfxWaveType::Noise:
            instrument.waveType =
                WaveType::Noise;
            break;
    }

    instrument.frequency =
        params.frequency;

    instrument.frequencySlide =
        params.frequencySlide;

    instrument.vibratoDepth =
        params.vibratoDepth;

    instrument.vibratoSpeed =
        params.vibratoSpeed;

    instrument.noiseMix =
        params.noiseMix;

    instrument.volume =
        params.volume;

    instrument.squareDuty =
        params.squareDuty;

    instrument.dutySweep =
        params.dutySweep;

    instrument.pitchJumpAmount =
        params.pitchJumpAmount;

    instrument.pitchJumpTime =
        params.pitchJumpTime;

    instrument.repeatSpeed =
        params.repeatSpeed;

    instrument.bitCrush =
        params.bitCrush;

    instrument.lowpassCutoff =
        params.lowpassCutoff;

    instrument.highpassCutoff =
        params.highpassCutoff;

    instrument.envelope.attack =
        params.attack;

    instrument.envelope.decay =
        params.decay;

    instrument.envelope.sustain =
        params.sustain;

    return instrument;
}
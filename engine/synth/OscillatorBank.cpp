#include "OscillatorBank.h"

void OscillatorBank::prepare(double sr)
{
    sampleRate = sr;

    if (primary)
        primary->prepare(sr);

    if (secondary)
        secondary->prepare(sr);

    if (noise)
        noise->prepare(sr);

    if (sub)
        sub->prepare(sr);
}

void OscillatorBank::setPrimary(
    std::unique_ptr<Oscillator> osc)
{
    primary = std::move(osc);

    if (primary)
        primary->prepare(sampleRate);
}

void OscillatorBank::setSecondary(
    std::unique_ptr<Oscillator> osc)
{
    secondary = std::move(osc);

    if (secondary)
        secondary->prepare(sampleRate);
}

void OscillatorBank::setNoise(
    std::unique_ptr<Oscillator> osc)
{
    noise = std::move(osc);

    if (noise)
        noise->prepare(sampleRate);
}

void OscillatorBank::setSub(
    std::unique_ptr<Oscillator> osc)
{
    sub = std::move(osc);

    if (sub)
        sub->prepare(sampleRate);
}

void OscillatorBank::setPrimaryFrequency(
    float frequency)
{
    if (primary)
        primary->setFrequency(frequency);
}

void OscillatorBank::setSecondaryFrequency(
    float frequency)
{
    if (secondary)
        secondary->setFrequency(frequency);
}

void OscillatorBank::setSubFrequency(
    float frequency)
{
    if (sub)
        sub->setFrequency(frequency);
}

void OscillatorBank::setDutyCycle(
    float duty)
{
    if (primary)
        primary->setDutyCycle(duty);

    if (secondary)
        secondary->setDutyCycle(duty);
}

void OscillatorBank::setPrimaryGain(
    float gain)
{
    primaryGain = gain;
}

void OscillatorBank::setSecondaryGain(
    float gain)
{
    secondaryGain = gain;
}

void OscillatorBank::setNoiseGain(
    float gain)
{
    noiseGain = gain;
}

void OscillatorBank::setSubGain(
    float gain)
{
    subGain = gain;
}

void OscillatorBank::reset()
{
    if (primary)
        primary->reset();

    if (secondary)
        secondary->reset();

    if (noise)
        noise->reset();

    if (sub)
        sub->reset();
}

float OscillatorBank::process()
{
    float sample = 0.0f;

    if (primary)
        sample += primary->process() * primaryGain;

    if (secondary)
        sample += secondary->process() * secondaryGain;

    if (noise)
        sample += noise->process() * noiseGain;

    if (sub)
        sample += sub->process() * subGain;

    return sample;
}
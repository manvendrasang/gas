#include "SynthEngine.h"

void SynthEngine::prepare(
    double sampleRate)
{
    voiceManager.prepare(
        sampleRate);

    mixer.setMasterGain(
        1.0f);

    mixer.setLimiter(
        1.0f);
}

void SynthEngine::noteOn(
    int midiNote,
    float velocity,
    const Instrument& instrument)
{
    voiceManager.noteOn(
        midiNote,
        velocity,
        instrument);
}

void SynthEngine::noteOff(
    int midiNote)
{
    voiceManager.noteOff(
        midiNote);
}

void SynthEngine::setPitchBend(
    float value)
{
    voiceManager.setPitchBend(
        value);
}

void SynthEngine::setModWheel(
    float value)
{
    voiceManager.setModWheel(
        value);
}

StereoSample SynthEngine::process()
{
    StereoSample sample =
        voiceManager.process();

    return
        mixer.process(
            sample);
}
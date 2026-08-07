#include "Voice.h"

#include "oscillators/SineOscillator.h"
#include "oscillators/SquareOscillator.h"
#include "oscillators/SawOscillator.h"
#include "oscillators/TriangleOscillator.h"
#include "oscillators/NoiseOscillator.h"
#include "MidiUtils.h"

void Voice::prepare(
    double sr)
{
    sampleRate = sr;

    oscillators.prepare(sr);

    processor.prepare(sr);
}

void Voice::reset()
{
    state = VoiceState{};

    info = VoiceInfo{};
}

void Voice::setInstrument(
    const Instrument& inst)
{
    reset();

    instrument = inst;

    state.currentFrequency =
    info.frequency;

    switch (inst.waveType)
    {
        case WaveType::Sine:
            oscillators.setPrimary(
                std::make_unique<SineOscillator>());
            break;

        case WaveType::Square:
            oscillators.setPrimary(
                std::make_unique<SquareOscillator>());
            break;

        case WaveType::Saw:
            oscillators.setPrimary(
                std::make_unique<SawOscillator>());
            break;

        case WaveType::Triangle:
            oscillators.setPrimary(
                std::make_unique<TriangleOscillator>());
            break;

        case WaveType::Noise:
            oscillators.setPrimary(
                std::make_unique<NoiseOscillator>());
            break;
    }

    oscillators.setPrimaryFrequency(
        inst.frequency);

    processor.setEnvelope(
        inst.envelope);

    noteOn();

    processor.setFilters(
        inst.lowpassCutoff,
        inst.highpassCutoff);

    processor.setBitCrush(
        inst.bitCrush);
}

float Voice::process()
{
    state.time +=
        1.0f /
        static_cast<float>(sampleRate);

    incrementAge();

    oscillators.setPrimaryFrequency(
        state.currentFrequency);

    oscillators.setDutyCycle(
        instrument.squareDuty);

    float sample =
        oscillators.process();

    sample =
        processor.process(
            state,
            sample,
            instrument.vibratoDepth,
            instrument.vibratoSpeed);

    return
        sample *
        instrument.volume *
        info.velocity;
}

void Voice::setMidiNote(
    int midiNote)
{
    info.midiNote =
        midiNote;

    info.frequency =
        MidiUtils::noteToFrequency(
            midiNote);

    state.currentFrequency =
        info.frequency;
}

int Voice::getMidiNote() const
{
    return
        info.midiNote;
}

float Voice::getFrequency() const
{
    return
        info.frequency;
}

bool Voice::isActive() const
{
    return info.active;
}

void Voice::setActive(
    bool active)
{
    info.active = active;
}

void Voice::setReleased(
    bool released)
{
    info.released = released;
}

bool Voice::isReleased() const
{
    return info.released;
}

void Voice::setSustained(
    bool sustained)
{
    info.sustained = sustained;
}

bool Voice::isSustained() const
{
    return info.sustained;
}

unsigned long Voice::getAge() const
{
    return info.age;
}

void Voice::incrementAge()
{
    ++info.age;
}

void Voice::resetAge()
{
    info.age = 0;
}

void Voice::noteOn()
{
    processor.noteOn();
}

void Voice::noteOff()
{
    processor.noteOff();
}

bool Voice::finished() const
{
    return
        !processor.isActive();
}

void Voice::setVelocity(
    float velocity)
{
    info.velocity = velocity;
}

float Voice::getVelocity() const
{
    return info.velocity;
}
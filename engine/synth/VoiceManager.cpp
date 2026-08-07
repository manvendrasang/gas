#include "VoiceManager.h"

VoiceManager::VoiceManager(
    int maxVoices)
    :
    voices(maxVoices),
    allocator(maxVoices)
{
}

void VoiceManager::prepare(
    double sampleRate)
{
    this->sampleRate = sampleRate;

    for (auto& voice : voices)
    {
        voice.prepare(sampleRate);
    }
}

void VoiceManager::noteOn(
    int midiNote,
    float velocity,
    const Instrument& instrument)
{
    int index = -1;

    for (size_t i = 0; i < voices.size(); ++i)
    {
        if (!voices[i].isActive())
        {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1)
    {
        index = allocator.allocate();
    }

    voices[index].reset();

    voices[index].setReleased(false);

    voices[index].setSustained(false);

    voices[index].setVelocity(
        velocity);

    voices[index].setMidiNote(
        midiNote);

    voices[index].setInstrument(
        instrument);

    voices[index].setActive(true);
}

void VoiceManager::noteOff(
    int midiNote)
{
    for (auto& voice : voices)
    {
        if (voice.isActive() &&
            voice.getMidiNote() == midiNote)
        {
            voice.setReleased(true);

            voice.noteOff();

            break;
        }
    }
}

float VoiceManager::process()
{
    float output = 0.0f;

    for (size_t i = 0; i < voices.size(); ++i)
    {
        auto& voice = voices[i];

        if (!voice.isActive())
            continue;

        output += voice.process();

        if (voice.finished())
        {
            voice.setActive(false);
            allocator.release(static_cast<int>(i));
        }
    }

    return output;
}
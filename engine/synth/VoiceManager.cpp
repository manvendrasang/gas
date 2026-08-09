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

    // setInstrument() performs its own internal reset() of the
    // voice's per-note state (VoiceInfo), so the note-specific
    // calls below must come after it - otherwise they get wiped
    // and every voice silently falls back to its VoiceInfo
    // defaults (midiNote 69, velocity 1.0) regardless of what
    // was actually requested here.
    voices[index].setInstrument(
        instrument);

    voices[index].setReleased(false);

    voices[index].setSustained(false);

    voices[index].setVelocity(
        velocity);

    voices[index].setMidiNote(
        midiNote);

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

StereoSample VoiceManager::process()
{
    StereoSample output;

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
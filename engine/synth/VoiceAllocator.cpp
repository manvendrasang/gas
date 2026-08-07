#include "VoiceAllocator.h"

VoiceAllocator::VoiceAllocator(
    int voiceCount)
    : active(voiceCount, false)
{
}

int VoiceAllocator::allocate()
{
    // Prefer an inactive voice.
    for (size_t i = 0; i < active.size(); ++i)
    {
        if (!active[i])
        {
            active[i] = true;
            nextVoice = static_cast<int>(i);
            return nextVoice;
        }
    }

    // Voice stealing (round-robin for now).
    nextVoice++;

    if (nextVoice >= static_cast<int>(active.size()))
        nextVoice = 0;

    active[nextVoice] = true;

    return nextVoice;
}

void VoiceAllocator::release(
    int index)
{
    if (index >= 0 &&
        index < static_cast<int>(active.size()))
    {
        active[index] = false;
    }
}
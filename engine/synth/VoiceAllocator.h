#pragma once

#include <vector>

class VoiceAllocator
{
public:
    explicit VoiceAllocator(int voiceCount = 32);

    int allocate();

    void release(int index);

private:
    std::vector<bool> active;

    int nextVoice = 0;
};
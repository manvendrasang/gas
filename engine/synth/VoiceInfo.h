#pragma once

struct VoiceInfo
{
    bool active = false;

    bool sustained = false;

    bool released = false;

    int midiNote = 69;

    float frequency = 440.0f;

    float velocity = 1.0f;

    unsigned long age = 0;
};
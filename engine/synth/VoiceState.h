#pragma once

#include "ModulationMatrix.h"
#include "AutomationLane.h"
#include "VoiceParameters.h"

struct VoiceState
{
    float currentFrequency = 440.0f;

    // Stage 14 - Portamento. When glideDuration > 0, currentFrequency
    // is being smoothly interpolated (linear in log2, i.e. constant
    // musical speed regardless of interval size) from
    // glideStartFrequency to glideTargetFrequency over glideDuration
    // seconds, tracked by glideElapsed. glideDuration defaults to 0
    // (no glide in progress), so this is a no-op unless something
    // explicitly starts a glide - see Voice::glideToMidiNote().
    float glideStartFrequency = 440.0f;

    float glideTargetFrequency = 440.0f;

    float glideDuration = 0.0f;

    float glideElapsed = 0.0f;

    float time = 0.0f;

    float repeatTimer = 0.0f;

    float crusherCounter = 0.0f;

    float heldSample = 0.0f;

    bool pitchJumpTriggered = false;

    float lfoPhase = 0.0f;

    VoiceParameters parameters;

    ModulationMatrix modulation;

    AutomationLane volumeAutomation;

    AutomationLane pitchAutomation;

    AutomationLane filterAutomation;
};
#pragma once

#include "ModulationMatrix.h"
#include "AutomationLane.h"
#include "VoiceParameters.h"

struct VoiceState
{
    float currentFrequency = 440.0f;

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
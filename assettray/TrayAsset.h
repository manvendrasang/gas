#pragma once

#include <string>

#include "../engine/synth/Instrument.h"

struct TrayAsset
{
    int id = 0;

    std::string name;

    Instrument instrument;

    bool favorite = false;

    bool selected = false;
};
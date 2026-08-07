#include "PresetBrowser.h"

SfxParameters
PresetBrowser::loadCoin()
{
    SfxParameters p;

    p.waveType =
        SfxWaveType::Square;

    p.frequency =
        1800.0f;

    p.frequencySlide =
        0.05f;

    p.decay =
        0.08f;

    return p;
}

SfxParameters
PresetBrowser::loadLaser()
{
    SfxParameters p;

    p.waveType =
        SfxWaveType::Square;

    p.frequency =
        1400.0f;

    p.frequencySlide =
        -0.8f;

    p.decay =
        0.2f;

    return p;
}

SfxParameters
PresetBrowser::loadExplosion()
{
    SfxParameters p;

    p.waveType =
        SfxWaveType::Noise;

    p.frequency =
        100.0f;

    p.noiseMix =
        1.0f;

    p.decay =
        0.6f;

    return p;
}
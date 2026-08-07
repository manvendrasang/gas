#include "MutationEngine.h"

#include <random>

float MutationEngine::randomRange(
    float min,
    float max)
{
    static std::mt19937 rng{
        std::random_device{}()
    };

    std::uniform_real_distribution<float>
        dist(min, max);

    return dist(rng);
}

std::vector<Instrument>
MutationEngine::generateVariations(
    const Instrument& base,
    int count)
{
    std::vector<Instrument>
        variations;

    for(int i = 0;
        i < count;
        ++i)
    {
        Instrument v = base;

        v.frequency *=
            randomRange(
                0.85f,
                1.15f);

        v.frequencySlide +=
            randomRange(
                -0.05f,
                0.05f);

        v.volume *=
            randomRange(
                0.90f,
                1.10f);

        v.noiseMix +=
            randomRange(
                -0.10f,
                0.10f);

        if(v.noiseMix < 0.0f)
            v.noiseMix = 0.0f;

        if(v.noiseMix > 1.0f)
            v.noiseMix = 1.0f;

        v.envelope.attack *=
            randomRange(
                0.8f,
                1.2f);

        v.envelope.decay *=
            randomRange(
                0.8f,
                1.2f);

        variations.push_back(v);
    }

    return variations;
}
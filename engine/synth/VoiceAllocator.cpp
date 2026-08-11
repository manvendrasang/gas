#include "VoiceAllocator.h"

int VoiceAllocator::chooseVoiceToSteal(
    const std::vector<bool>& released,
    const std::vector<unsigned long>& ages)
{
    int bestIndex = 0;

    bool bestIsReleased = false;

    unsigned long bestAge = 0;

    bool found = false;

    for (size_t i = 0; i < released.size(); ++i)
    {
        const bool candidateReleased =
            released[i];

        const unsigned long candidateAge =
            ages[i];

        if (!found)
        {
            bestIndex = static_cast<int>(i);

            bestIsReleased = candidateReleased;

            bestAge = candidateAge;

            found = true;

            continue;
        }

        // A released voice always beats a sustaining one,
        // regardless of age - it's already fading out.
        if (candidateReleased && !bestIsReleased)
        {
            bestIndex = static_cast<int>(i);

            bestIsReleased = candidateReleased;

            bestAge = candidateAge;

            continue;
        }

        // Never downgrade from a released best candidate to a
        // sustaining one.
        if (bestIsReleased && !candidateReleased)
            continue;

        // Same release-state tier: prefer whichever has been
        // sounding the longest.
        if (candidateAge > bestAge)
        {
            bestIndex = static_cast<int>(i);

            bestAge = candidateAge;
        }
    }

    return bestIndex;
}

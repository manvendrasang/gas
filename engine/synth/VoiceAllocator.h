#pragma once

#include <vector>

// Stage 15 - Improved Voice Stealing.
//
// This class's only job is deciding WHICH voice to steal when the
// pool is completely full - VoiceManager confirms that condition
// itself (by scanning for a free voice first) and only asks here
// once none was found.
//
// It used to also keep its own bookkeeping of which voices were
// active (a separate `active[]` bitmask, updated only by its own
// allocate()/release() pair), but VoiceManager's free-voice path -
// the common case - never went through that pair; it checked
// Voice::isActive() directly instead. The result: the allocator's
// bookkeeping almost never reflected which voices were actually
// active, so its "round-robin" stealing was effectively picking an
// arbitrary index rather than a genuinely informed choice most of
// the time.
//
// Taking the real per-voice state as input here instead removes
// that entire class of bug by construction: there's nothing left
// to go out of sync with, because there's no separate bookkeeping
// left to maintain.
class VoiceAllocator
{
public:

    // released[i] / ages[i] must correspond to voice slot i (i.e.
    // Voice[i].isReleased() / Voice[i].getAge()) for a pool where
    // every voice is currently active - both vectors the same
    // size as the voice pool.
    //
    // Prefers stealing a voice that's already in its release tail
    // over one still sustaining: it's fading out and about to
    // finish anyway, so interrupting it is the least audible
    // choice available. Among equally-eligible voices (both
    // released, or both still sustaining), prefers the oldest -
    // it's most likely to have already been heard, and least
    // likely to be a note the player just triggered.
    static int chooseVoiceToSteal(
        const std::vector<bool>& released,
        const std::vector<unsigned long>& ages);
};

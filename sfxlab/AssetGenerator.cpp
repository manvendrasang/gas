#include "AssetGenerator.h"

#include "MutationEngine.h"
#include "presets/CoinPreset.h"

void AssetGenerator::generateCoinSet(
    AssetTray& tray,
    int count)
{
    MutationEngine mutator;

    auto variations =
        mutator.generateVariations(
            CoinPreset(),
            count);

    int id = 1;

    for (auto& sound : variations)
    {
        TrayAsset asset;

        asset.id = id;

        asset.name =
            "Coin_" +
            std::to_string(id);

        asset.instrument =
            sound;

        tray.addAsset(asset);

        ++id;
    }
}
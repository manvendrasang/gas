#pragma once

#include "TrayAsset.h"

#include <vector>

class AssetTray
{
public:

    void addAsset(
        const TrayAsset& asset);

    void removeAsset(
        int id);

    void clear();

    TrayAsset* find(
        int id);

    std::vector<TrayAsset>&
    getAssets();

private:

    std::vector<TrayAsset>
        assets;
};
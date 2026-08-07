#include "AssetTray.h"
#include <algorithm>

void AssetTray::addAsset(
    const TrayAsset& asset)
{
    assets.push_back(asset);
}

void AssetTray::removeAsset(
    int id)
{
    assets.erase(
        std::remove_if(
            assets.begin(),
            assets.end(),
            [id](const TrayAsset& a)
            {
                return a.id == id;
            }),
        assets.end());
}

void AssetTray::clear()
{
    assets.clear();
}

TrayAsset* AssetTray::find(
    int id)
{
    for(auto& asset : assets)
    {
        if(asset.id == id)
            return &asset;
    }

    return nullptr;
}

std::vector<TrayAsset>&
AssetTray::getAssets()
{
    return assets;
}
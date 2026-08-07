#pragma once

#include "TrayAsset.h"

class AssetPreviewer
{
public:

    void preview(
        const TrayAsset& asset);

    void exportAsset(
        const TrayAsset& asset,
        const std::string& path);
};
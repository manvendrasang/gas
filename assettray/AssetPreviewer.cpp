#include "AssetPreviewer.h"

#include "../engine/synth/AudioRenderer.h"
#include "../engine/export/WaveExporter.h"

void AssetPreviewer::exportAsset(
    const TrayAsset& asset,
    const std::string& path)
{
    AudioRenderer renderer;

    auto buffer =
        renderer.render(
            asset.instrument,
            0.5f);

    WaveExporter exporter;

    exporter.write(
        path,
        buffer);
}

void AssetPreviewer::preview(
    const TrayAsset& asset)
{
    exportAsset(
        asset,
        "__preview.wav");
}
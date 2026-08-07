#include "PreviewController.h"

#include "../../sfxlab/builders/InstrumentBuilder.h"

#include "../../engine/synth/AudioRenderer.h"
#include "../../engine/export/WaveExporter.h"

void PreviewController::preview(
    const SfxParameters& params)
{
    Instrument instrument =
        InstrumentBuilder::build(
            params);

    AudioRenderer renderer;

    auto buffer =
        renderer.render(
            instrument,
            0.5f);

    WaveExporter exporter;

    exporter.write(
        "__preview.wav",
        buffer);
}
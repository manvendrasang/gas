cmake_minimum_required(VERSION 3.20)

project(GameAudioStudio)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GameAudioStudio

    app/main.cpp

    engine/synth/ADSR.cpp
    engine/synth/AudioRenderer.cpp
    engine/synth/SynthVoice.cpp
    engine/synth/OscillatorBank.cpp
    engine/synth/Voice.cpp
    engine/synth/VoiceManager.cpp
    engine/synth/SynthEngine.cpp
    engine/synth/VoiceMixer.cpp
    engine/synth/ModulationMatrix.cpp
    engine/synth/AutomationLane.cpp
    engine/synth/LFO.cpp
    engine/synth/EnvelopeGenerator.cpp
    engine/synth/VoiceParameters.cpp
    engine/synth/VoiceAllocator.cpp
    engine/synth/VoiceInfo.cpp
    engine/synth/MidiUtils.cpp
    engine/synth/VoiceProcessor.cpp

    engine/export/WaveExporter.cpp

    assettray/AssetTray.cpp
    assettray/AssetPreviewer.cpp

    sfxlab/generators/CoinGenerator.cpp
    sfxlab/generators/LaserGenerator.cpp
    sfxlab/generators/ExplosionGenerator.cpp
    sfxlab/generators/JumpGenerator.cpp
    sfxlab/generators/PowerupGenerator.cpp
    sfxlab/generators/HitGenerator.cpp
    sfxlab/generators/UIClickGenerator.cpp
    
    sfxlab/SfxFactory.cpp
    sfxlab/AssetGenerator.cpp
    sfxlab/MutationEngine.cpp

    sfxlab/builders/InstrumentBuilder.cpp

    app/editor/ParameterEditor.cpp
    app/editor/PresetBrowser.cpp
    app/editor/PreviewController.cpp

    engine/audio/AudioPlayer.cpp
    engine/audio/Miniaudio.cpp
)
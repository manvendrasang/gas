#include <thread>
#include <chrono>

#include "../engine/audio/AudioPlayer.h"

#include "../sfxlab/SfxFactory.h"
#include "../engine/synth/AudioRenderer.h"

int main()
{
    AudioPlayer player;

    if (!player.initialize())
        return -1;

    AudioRenderer renderer;

    auto generator =
        SfxFactory::create(
            SfxType::Coin);

    auto sound =
        renderer.render(
            generator->generate(),
            0.5f);

    player.play(sound);

    std::this_thread::sleep_for(
        std::chrono::milliseconds(
            1000));

    player.shutdown();

    return 0;
}
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Emulator.h"

SaveManager saveManager;

bool Emulator::init(
    const char *corePath,
    const char *romPath)
{
    if (SDL_Init(
            SDL_INIT_VIDEO |
            SDL_INIT_AUDIO |
            SDL_INIT_GAMECONTROLLER) != 0)
    {
        std::cout
            << "SDL init failed: "
            << SDL_GetError()
            << std::endl;

        return false;
    }

    if (!saveManager.init())
    {
        std::cout
            << "Save manager initialization failed\n";

        return false;
    }

    if (!video.init())
    {
        std::cout
            << "Video initialization failed\n";

        shutdown();
        return false;
    }

    if (!audio.init())
    {
        std::cout
            << "Audio initialization failed\n";

        shutdown();
        return false;
    }

    if (!loader.load(corePath))
    {
        std::cout
            << "Failed to load core DLL\n";

        shutdown();
        return false;
    }

    if (!core.load(loader))
    {
        std::cout
            << "Failed to load libretro functions\n";

        shutdown();
        return false;
    }

    core.setAudioManager(&audio);

    core.setVideoRenderer(&video);

    core.setInputManager(&input);

    core.init();

    if (!core.loadGame(romPath))
    {
        std::cout
            << "Failed to load ROM\n";

        shutdown();
        return false;
    }

    limiter.setFPS(
        core.getFPS());

    running = true;

    return true;
}

void Emulator::run()
{
    while (running)
    {
        running =
            video.processEvents();

        input.update();

        if (input.savePressed())
        {
            saveTestState();
        }

        if (input.loadPressed())
        {
            loadTestState();
        }

        core.runFrame();

        video.render();

        limiter.wait();
    }
}

void Emulator::shutdown()
{
    video.shutdown();

    audio.shutdown();

    core.shutdown();

    SDL_Quit();
}

void Emulator::saveTestState()
{
    std::vector<uint8_t> buffer;

    if (!core.saveState(buffer))
    {
        std::cout << "Save failed\n";
        return;
    }

    if (saveManager.saveState(
            "ChronoTrigger.slot0",
            buffer))
    {
        std::cout << "State saved!\n";
    }
    else
    {
        std::cout << "Failed writing save file\n";
    }
}

void Emulator::loadTestState()
{
    std::vector<uint8_t> buffer;

    if (!saveManager.loadState(
            "ChronoTrigger.slot0",
            buffer))
    {
        std::cout << "Failed reading save file\n";
        return;
    }

    if (core.loadState(buffer))
    {
        std::cout << "State loaded!\n";
    }
    else
    {
        std::cout << "Load failed\n";
    }
}
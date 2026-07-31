#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Emulator.h"

std::vector<uint8_t> testSave;

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
    if (core.saveState(testSave))
    {
        std::cout << "State saved!\n";
    }
    else
    {
        std::cout << "Save failed\n";
    }
}

void Emulator::loadTestState()
{
    if (core.loadState(testSave))
    {
        std::cout << "State loaded!\n";
    }
    else
    {
        std::cout << "Load failed\n";
    }
}
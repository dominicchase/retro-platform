#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include "CoreLoader.h"
#include "LibretroCore.h"
#include "VideoRenderer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "FrameLimiter.h"

int main(int argc, char *argv[])
{
    std::cout << "argc: " << argc << "\n";

    for (int i = 0; i < argc; i++)
    {
        std::cout << "argv[" << i << "]: "
                  << argv[i]
                  << "\n";
    }

    if (argc < 3)
    {
        std::cout
            << "Usage: libretro-runner <core.dll> <rom>\n";
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
    {
        std::cout
            << "SDL init failed: "
            << SDL_GetError()
            << std::endl;

        return 1;
    }

    CoreLoader loader;

    if (!loader.load(argv[1]))
    {
        std::cout << "Failed to load core DLL\n";
        return 1;
    }

    LibretroCore core;

    if (!core.load(loader))
    {
        std::cout << "Failed to load libretro functions\n";
        return 1;
    }

    core.init();

    if (!core.loadGame(argv[2]))
    {
        std::cout << "Failed to load ROM\n";
        return 1;
    }

    std::cout << "ROM loaded!\n";

    FrameLimiter limiter;

    limiter.setFPS(
        core.getFPS());

    VideoRenderer video;

    if (!video.init())
    {
        return 1;
    }

    AudioManager audio;

    if (!audio.init())
    {
        return 1;
    }

    core.setAudioManager(&audio);

    InputManager input;

    core.setInputManager(&input);

    bool running = true;

    while (running)
    {
        running = video.processEvents();

        input.update();

        core.runFrame();

        video.render(
            g_frameBuffer,
            g_frameWidth,
            g_frameHeight,
            g_framePitch);

      limiter.wait();
    }

    video.shutdown();
    audio.shutdown();

    SDL_Quit();

    return 0;
}
#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include "CoreLoader.h"
#include "LibretroCore.h"

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

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL init failed: "
                  << SDL_GetError()
                  << std::endl;

        return 1;
    }

    SDL_Window *window =
        SDL_CreateWindow(
            "Retro Platform",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            512,
            448,
            0);

    if (!window)
    {
        std::cout << "SDL window failed: "
                  << SDL_GetError()
                  << std::endl;

        return 1;
    }

    SDL_Renderer *renderer =
        SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cout << "SDL renderer failed: "
                  << SDL_GetError()
                  << std::endl;

        return 1;
    }

    SDL_Texture *texture =
        SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGB565,
            SDL_TEXTUREACCESS_STREAMING,
            256,
            224);

    if (!texture)
    {
        std::cout << "SDL texture failed: "
                  << SDL_GetError()
                  << std::endl;

        return 1;
    }

    std::cout << "SDL window created\n";

    bool running = true;

    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        core.runFrame();

        if (g_frameBuffer)
        {
            SDL_UpdateTexture(
                texture,
                nullptr,
                g_frameBuffer,
                static_cast<int>(g_framePitch));

            SDL_RenderClear(renderer);

            SDL_RenderCopy(
                renderer,
                texture,
                nullptr,
                nullptr);

            SDL_RenderPresent(renderer);
        }

        SDL_Delay(16);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
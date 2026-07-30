#include "VideoRenderer.h"
#include <iostream>

bool VideoRenderer::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL init failed: "
                  << SDL_GetError()
                  << std::endl;

        return false;
    }

    window =
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

        return false;
    }

    renderer =
        SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cout << "SDL renderer failed: "
                  << SDL_GetError()
                  << std::endl;

        return false;
    }

    texture =
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

        return false;
    }

    return true;
}

void VideoRenderer::render(
    const void *frameBuffer,
    unsigned width,
    unsigned height,
    size_t pitch)
{
    if (!frameBuffer)
    {
        return;
    }

    SDL_UpdateTexture(
        texture,
        nullptr,
        frameBuffer,
        static_cast<int>(pitch));

    SDL_RenderClear(renderer);

    SDL_RenderCopy(
        renderer,
        texture,
        nullptr,
        nullptr);

    SDL_RenderPresent(renderer);
}

void VideoRenderer::shutdown()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

bool VideoRenderer::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }

    return true;
}
#pragma once

#include <SDL2/SDL.h>

class VideoRenderer
{
public:
    bool init();

    void render(
        const void *frameBuffer,
        unsigned width,
        unsigned height,
        size_t pitch);

    bool processEvents();

    void delay();

    void shutdown();

private:
    SDL_Window *window = nullptr;

    SDL_Renderer *renderer = nullptr;

    SDL_Texture *texture = nullptr;
};
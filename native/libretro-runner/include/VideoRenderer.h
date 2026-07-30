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

    void shutdown();

    bool processEvents();

private:
    SDL_Window *window = nullptr;

    SDL_Renderer *renderer = nullptr;

    SDL_Texture *texture = nullptr;
};
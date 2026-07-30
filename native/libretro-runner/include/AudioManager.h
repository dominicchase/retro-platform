#pragma once

#include <SDL2/SDL.h>
#include <cstddef>
#include <cstdint>

class AudioManager
{
public:
    bool init();

    void playSamples(
        const int16_t *samples,
        size_t frameCount);

    void shutdown();

private:
    SDL_AudioDeviceID device = 0;
};
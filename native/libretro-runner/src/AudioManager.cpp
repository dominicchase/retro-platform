#include "AudioManager.h"

#include <iostream>

bool AudioManager::init()
{
    SDL_AudioSpec desired{};
    SDL_AudioSpec obtained{};

    desired.freq = 32040;
    desired.format = AUDIO_S16SYS;
    desired.channels = 2;
    desired.samples = 1024;
    desired.callback = nullptr;

    device =
        SDL_OpenAudioDevice(
            nullptr,
            0,
            &desired,
            &obtained,
            0);

    if (device == 0)
    {
        std::cout
            << "SDL audio failed: "
            << SDL_GetError()
            << std::endl;

        return false;
    }

    SDL_PauseAudioDevice(device, 0);

    std::cout
        << "Audio initialized: "
        << obtained.freq
        << " Hz"
        << std::endl;

    return true;
}

void AudioManager::playSamples(
    const int16_t *samples,
    size_t frameCount)
{
    if (!device)
    {
        return;
    }

    SDL_QueueAudio(
        device,
        samples,
        frameCount * sizeof(int16_t) * 2);
}

void AudioManager::shutdown()
{
    if (device)
    {
        SDL_CloseAudioDevice(device);
        device = 0;
    }
}
#pragma once

#include "CoreLoader.h"
#include "LibretroCore.h"
#include "VideoRenderer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "FrameLimiter.h"

class Emulator
{
public:
    bool init(
        const char *corePath,
        const char *romPath);

    void run();

    void shutdown();

private:
    CoreLoader loader;

    LibretroCore core;

    VideoRenderer video;

    AudioManager audio;

    InputManager input;

    FrameLimiter limiter;

    bool running = false;
};
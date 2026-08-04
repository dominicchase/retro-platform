#pragma once

#include <string>

#include "CoreLoader.h"
#include "LibretroCore.h"
#include "VideoRenderer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "FrameLimiter.h"
#include "SaveManager.h"

class Emulator
{
public:
    bool init(
        const char *corePath,
        const char *romPath);

    void run();

    void shutdown();

    void saveTestState();

    void loadTestState();

    std::string getSaveFilename(int slot) const;

private:
    CoreLoader loader;

    LibretroCore core;

    VideoRenderer video;

    AudioManager audio;

    InputManager input;

    FrameLimiter limiter;

    SaveManager saveManager;

    bool running = false;

    std::string currentGameName;

    int currentSaveSlot = 0;
};
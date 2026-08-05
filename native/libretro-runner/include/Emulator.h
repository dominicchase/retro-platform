#pragma once

#include <string>

#include "CoreLoader.h"
#include "LibretroCore.h"
#include "VideoRenderer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "FrameLimiter.h"
#include "SaveManager.h"
#include "EmulatorState.h"
#include "EmulatorCommand.h"
#include "EmulatorCommandQueue.h"

class Emulator
{
public:
    bool init(
        const char *corePath,
        const char *romPath);

    void run();

    void shutdown();

    void saveState();

    void loadState();

    std::string getSaveFilename(int slot) const;

    void changeSaveSlot(int amount);

    void handleCommand(EmulatorCommand command);

    void pause();

    void resume();

    void stop();

    int getCurrentSlot() const;

    void setCurrentSlot(int slot);

    void queueCommand(
        EmulatorCommand command);

private:
    void updateSaveMenu();

    CoreLoader loader;

    LibretroCore core;

    VideoRenderer video;

    AudioManager audio;

    InputManager input;

    FrameLimiter limiter;

    SaveManager saveManager;

    bool running = false;

    EmulatorState state;

    EmulatorCommandQueue commandQueue;
};
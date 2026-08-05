#pragma once

#include <thread>

#include "EmulatorController.h"
#include "Emulator.h"

class EmulatorRunner
{
public:
    bool start(
        const char *corePath,
        const char *romPath);

    void stop();

    EmulatorController &controller();

    void pause();

    void resume();

    void save();

    void load();

private:
    Emulator emulator;

    EmulatorController emulatorController{&emulator};

    std::thread emulatorThread;
};
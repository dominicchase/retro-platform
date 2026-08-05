#pragma once

#include "Emulator.h"

class EmulatorController
{
public:
    EmulatorController(Emulator *emulator);

    void pause();

    void resume();

    void save();

    void load();

    int getCurrentSlot();

    void setSlot(int slot);

private:
    Emulator *emulator;
};
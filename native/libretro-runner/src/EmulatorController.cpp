#include "EmulatorController.h"

EmulatorController::EmulatorController(
    Emulator *emulator)
{
    this->emulator = emulator;
}

void EmulatorController::pause()
{
    emulator->pause();
}

void EmulatorController::resume()
{
    emulator->resume();
}

void EmulatorController::save()
{
    emulator->saveState();
}

void EmulatorController::load()
{
    emulator->loadState();
}

int EmulatorController::getCurrentSlot()
{
    return emulator->getCurrentSlot();
}

void EmulatorController::setSlot(int slot)
{
    emulator->setCurrentSlot(slot);
}
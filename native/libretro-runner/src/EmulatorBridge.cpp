#include "EmulatorBridge.h"
#include "EmulatorController.h"

static EmulatorController *controller = nullptr;

void setEmulatorController(
    EmulatorController *instance)
{
    controller = instance;
}

void emulatorPause()
{
    if (controller)
    {
        controller->pause();
    }
}

void emulatorResume()
{
    if (controller)
    {
        controller->resume();
    }
}

void emulatorSave()
{
    if (controller)
    {
        controller->save();
    }
}

void emulatorLoad()
{
    if (controller)
    {
        controller->load();
    }
}

int emulatorGetCurrentSlot()
{
    if (controller)
    {
        return controller->getCurrentSlot();
    }

    return -1;
}

void emulatorSetSlot(int slot)
{
    if (controller)
    {
        controller->setSlot(slot);
    }
}
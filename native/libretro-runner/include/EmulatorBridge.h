#pragma once

#ifdef __cplusplus

class EmulatorController;

extern "C"
{

#endif

    void setEmulatorController(
        EmulatorController *controller);

    void emulatorPause();

    void emulatorResume();

    void emulatorSave();

    void emulatorLoad();

    int emulatorGetCurrentSlot();

    void emulatorSetSlot(int slot);

#ifdef __cplusplus
}

#endif
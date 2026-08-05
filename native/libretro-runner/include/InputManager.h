#pragma once

#include <SDL2/SDL.h>
#include "EmulatorCommand.h"

struct ButtonState
{
    bool current = false;
    bool previous = false;

    bool pressed()
    {
        return current && !previous;
    }
};

class InputManager
{
public:
    void update();

    int getButtonState(unsigned id);

    bool savePressed();

    bool loadPressed();

    bool nextSlotPressed();

    bool previousSlotPressed();

    void endFrame();

    bool pausePressed();

    bool menuPressed();

    EmulatorCommand getCommand();

private:
    bool buttons[16] = {};

    SDL_GameController *controller = nullptr;

    ButtonState saveButton;

    ButtonState loadButton;

    ButtonState nextSlotButton;

    ButtonState previousSlotButton;

    ButtonState pauseButton;

    ButtonState menuButton;
};
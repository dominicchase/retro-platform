#pragma once

#include <SDL2/SDL.h>

class InputManager
{
public:
    void update();

    int getButtonState(unsigned id);

private:
    bool buttons[16] = {};

    SDL_GameController* controller = nullptr;
};
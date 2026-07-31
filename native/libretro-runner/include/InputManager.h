#pragma once

#include <SDL2/SDL.h>

class InputManager
{
public:
    void update();

    int getButtonState(unsigned id);

    bool savePressed();

    bool loadPressed();

private:
    bool buttons[16] = {};

    SDL_GameController *controller = nullptr;

    bool save = false;

    bool load = false;
};
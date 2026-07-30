#include "InputManager.h"
#include "libretro.h"
#include <SDL2/SDL.h>

int InputManager::getButtonState(unsigned id)
{
    if (id >= 16)
    {
        return 0;
    }

    return buttons[id] ? 1 : 0;
}

void InputManager::update()
{
    SDL_PumpEvents();

    const Uint8 *keyboard =
        SDL_GetKeyboardState(nullptr);

    buttons[RETRO_DEVICE_ID_JOYPAD_UP] =
        keyboard[SDL_SCANCODE_UP];

    buttons[RETRO_DEVICE_ID_JOYPAD_DOWN] =
        keyboard[SDL_SCANCODE_DOWN];

    buttons[RETRO_DEVICE_ID_JOYPAD_LEFT] =
        keyboard[SDL_SCANCODE_LEFT];

    buttons[RETRO_DEVICE_ID_JOYPAD_RIGHT] =
        keyboard[SDL_SCANCODE_RIGHT];

    buttons[RETRO_DEVICE_ID_JOYPAD_B] =
        keyboard[SDL_SCANCODE_Z];

    buttons[RETRO_DEVICE_ID_JOYPAD_A] =
        keyboard[SDL_SCANCODE_X];

    buttons[RETRO_DEVICE_ID_JOYPAD_Y] =
        keyboard[SDL_SCANCODE_A];

    buttons[RETRO_DEVICE_ID_JOYPAD_X] =
        keyboard[SDL_SCANCODE_S];

    buttons[RETRO_DEVICE_ID_JOYPAD_START] =
        keyboard[SDL_SCANCODE_RETURN];

    buttons[RETRO_DEVICE_ID_JOYPAD_SELECT] =
        keyboard[SDL_SCANCODE_RSHIFT];

    buttons[RETRO_DEVICE_ID_JOYPAD_L] =
        keyboard[SDL_SCANCODE_Q];

    buttons[RETRO_DEVICE_ID_JOYPAD_R] =
        keyboard[SDL_SCANCODE_W];
}
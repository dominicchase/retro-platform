#include <iostream>
#include <SDL2/SDL.h>
#include "libretro.h"
#include "InputManager.h"

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
    if (!controller)
    {
        if (SDL_NumJoysticks() > 0 &&
            SDL_IsGameController(0))
        {
            controller = SDL_GameControllerOpen(0);

            if (controller)
            {
                std::cout
                    << "Controller connected: "
                    << SDL_GameControllerName(controller)
                    << std::endl;
            }
        }
    }

    SDL_PumpEvents();

    const Uint8 *keyboard =
        SDL_GetKeyboardState(nullptr);

    saveButton.current =
        keyboard[SDL_SCANCODE_F];

    loadButton.current =
        keyboard[SDL_SCANCODE_G];

    nextSlotButton.current =
        keyboard[SDL_SCANCODE_N];

    previousSlotButton.current =
        keyboard[SDL_SCANCODE_P];

    buttons[RETRO_DEVICE_ID_JOYPAD_UP] =
        keyboard[SDL_SCANCODE_UP] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_DPAD_UP));

    buttons[RETRO_DEVICE_ID_JOYPAD_DOWN] =
        keyboard[SDL_SCANCODE_DOWN] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_DPAD_DOWN));

    buttons[RETRO_DEVICE_ID_JOYPAD_LEFT] =
        keyboard[SDL_SCANCODE_LEFT] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_DPAD_LEFT));

    buttons[RETRO_DEVICE_ID_JOYPAD_RIGHT] =
        keyboard[SDL_SCANCODE_RIGHT] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_DPAD_RIGHT));

    buttons[RETRO_DEVICE_ID_JOYPAD_B] =
        keyboard[SDL_SCANCODE_Z] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_A));

    buttons[RETRO_DEVICE_ID_JOYPAD_A] =
        keyboard[SDL_SCANCODE_X] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_B));

    buttons[RETRO_DEVICE_ID_JOYPAD_Y] =
        keyboard[SDL_SCANCODE_A] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_X));

    buttons[RETRO_DEVICE_ID_JOYPAD_X] =
        keyboard[SDL_SCANCODE_S] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_Y));

    buttons[RETRO_DEVICE_ID_JOYPAD_START] =
        keyboard[SDL_SCANCODE_RETURN] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_START));

    buttons[RETRO_DEVICE_ID_JOYPAD_SELECT] =
        keyboard[SDL_SCANCODE_RSHIFT] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_BACK));

    buttons[RETRO_DEVICE_ID_JOYPAD_L] =
        keyboard[SDL_SCANCODE_Q] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_LEFTSHOULDER));

    buttons[RETRO_DEVICE_ID_JOYPAD_R] =
        keyboard[SDL_SCANCODE_W] ||
        (controller &&
         SDL_GameControllerGetButton(
             controller,
             SDL_CONTROLLER_BUTTON_RIGHTSHOULDER));

    pauseButton.current =
        keyboard[SDL_SCANCODE_ESCAPE];

    menuButton.current =
        keyboard[SDL_SCANCODE_M];
}

bool InputManager::savePressed()
{
    return saveButton.pressed();
}

bool InputManager::loadPressed()
{
    return loadButton.pressed();
}

bool InputManager::nextSlotPressed()
{
    return nextSlotButton.pressed();
}

bool InputManager::previousSlotPressed()
{
    return previousSlotButton.pressed();
}

bool InputManager::pausePressed()
{
    return pauseButton.pressed();
}

bool InputManager::menuPressed()
{
    return menuButton.pressed();
}

void InputManager::endFrame()
{
    saveButton.previous =
        saveButton.current;

    loadButton.previous =
        loadButton.current;

    nextSlotButton.previous =
        nextSlotButton.current;

    previousSlotButton.previous =
        previousSlotButton.current;

    pauseButton.previous =
        pauseButton.current;

    menuButton.previous =
        menuButton.current;
}
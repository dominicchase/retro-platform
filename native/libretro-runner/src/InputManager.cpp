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
    // SDL keyboard polling will go here next
}
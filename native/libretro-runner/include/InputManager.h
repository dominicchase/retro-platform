#pragma once

class InputManager
{
public:
    void update();

    int getButtonState(unsigned id);

private:
    bool buttons[16] = {};
};
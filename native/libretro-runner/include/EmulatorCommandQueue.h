#pragma once

#include <queue>
#include <mutex>

#include "EmulatorCommand.h"

class EmulatorCommandQueue
{
public:
    void push(EmulatorCommand command);

    EmulatorCommand pop();

private:
    std::queue<EmulatorCommand> commands;

    std::mutex mutex;
};
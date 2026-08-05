#include "EmulatorCommandQueue.h"

void EmulatorCommandQueue::push(
    EmulatorCommand command)
{
    std::lock_guard<std::mutex> lock(mutex);

    commands.push(command);
}

EmulatorCommand EmulatorCommandQueue::pop()
{
    std::lock_guard<std::mutex> lock(mutex);

    if (commands.empty())
    {
        return EmulatorCommand::None;
    }

    EmulatorCommand command = commands.front();

    commands.pop();

    return command;
}
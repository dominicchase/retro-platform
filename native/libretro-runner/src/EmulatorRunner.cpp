#include "EmulatorRunner.h"

bool EmulatorRunner::start(
    const char *corePath,
    const char *romPath)
{
    if (!emulator.init(corePath, romPath))
    {
        return false;
    }

    emulatorThread =
        std::thread([this]()
                    { emulator.run(); });

    return true;
}

void EmulatorRunner::stop()
{
    emulator.stop();

    if (emulatorThread.joinable())
    {
        emulatorThread.join();
    }

    emulator.shutdown();
}

void EmulatorRunner::pause()
{
    emulator.queueCommand(
        EmulatorCommand::Pause);
}

void EmulatorRunner::resume()
{
    emulator.queueCommand(
        EmulatorCommand::Resume);
}

void EmulatorRunner::save()
{
    emulator.queueCommand(
        EmulatorCommand::Save);
}

void EmulatorRunner::load()
{
    emulator.queueCommand(
        EmulatorCommand::Load);
}

EmulatorController &EmulatorRunner::controller()
{
    return emulatorController;
}
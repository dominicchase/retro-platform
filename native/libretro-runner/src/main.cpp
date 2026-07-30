#define SDL_MAIN_HANDLED

#include "Emulator.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout
            << "Usage: libretro-runner <core.dll> <rom>\n";

        return 1;
    }

    Emulator emulator;

    if (!emulator.init(
            argv[1],
            argv[2]))
    {
        return 1;
    }

    emulator.run();

    emulator.shutdown();

    return 0;
}
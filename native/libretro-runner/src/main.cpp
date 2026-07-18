#include <iostream>
#include "CoreLoader.h"
#include "LibretroCore.h"

int main(int argc, char *argv[])
{
    CoreLoader loader;

    if (!loader.load(argv[1]))
    {
        return 1;
    }

    LibretroCore core;

    if (!core.load(loader))
    {
        return 1;
    }

    core.init();

    if (!core.loadGame(
            "C:/GitHub/retro-platform/data/games/SNES/Chrono Trigger.smc"))
    {
        std::cout << "Failed to load ROM\n";
        return 1;
    }

    std::cout << "ROM loaded!\n";

    return 0;
}
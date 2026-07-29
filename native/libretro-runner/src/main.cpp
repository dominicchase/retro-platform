#include <iostream>
#include "CoreLoader.h"
#include "LibretroCore.h"

int main(int argc, char *argv[])
{
    std::cout << "argc: " << argc << "\n";

    for (int i = 0; i < argc; i++)
    {
        std::cout << "argv[" << i << "]: "
                  << argv[i]
                  << "\n";
    }

    if (argc < 3)
    {
        std::cout
            << "Usage: libretro-runner <core.dll> <rom>\n";
        return 1;
    }

    CoreLoader loader;

    if (!loader.load(argv[1]))
    {
        std::cout << "Failed to load core DLL\n";
        return 1;
    }

    LibretroCore core;

    if (!core.load(loader))
    {
        std::cout << "Failed to load libretro functions\n";
        return 1;
    }

    core.init();

    if (!core.loadGame(argv[2]))
    {
        std::cout << "Failed to load ROM\n";
        return 1;
    }

    std::cout << "ROM loaded!\n";

    return 0;
}
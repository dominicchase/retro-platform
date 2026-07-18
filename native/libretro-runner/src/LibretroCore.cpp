#include "LibretroCore.h"
#include <iostream>

bool environment_callback(unsigned cmd, void *data)
{
    std::cout << "Environment command: "
              << cmd
              << std::endl;

    return false;
}

bool LibretroCore::load(CoreLoader &loader)
{
    retro_init =
        reinterpret_cast<void (*)()>(
            loader.getFunction("retro_init"));

    retro_set_environment =
        reinterpret_cast<void (*)(retro_environment_t)>(
            loader.getFunction("retro_set_environment"));

    if (!retro_init || !retro_set_environment)
    {
        std::cout << "Failed to load libretro functions\n";
        return false;
    }

    return true;

    retro_load_game =
        reinterpret_cast<bool (*)(const retro_game_info *)>(
            loader.getFunction("retro_load_game"));

    if (!retro_load_game)
    {
        std::cout << "Failed to find retro_load_game\n";
        return false;
    }
}

void LibretroCore::init()
{
    retro_set_environment(environment_callback);

    std::cout << "Calling retro_init...\n";

    retro_init();

    std::cout << "Core initialized\n";
}

bool LibretroCore::loadGame(const std::string &path)
{
    retro_game_info gameInfo{};

    gameInfo.path = path.c_str();

    std::cout << "Loading ROM: "
              << gameInfo.path
              << std::endl;

    return retro_load_game(&gameInfo);
}

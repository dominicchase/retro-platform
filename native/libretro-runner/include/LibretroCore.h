#pragma once

#include "libretro.h"
#include "CoreLoader.h"

class LibretroCore
{
public:
    bool load(CoreLoader& loader);
    void init();
    bool loadGame(const std::string& path);

private:
    void (*retro_init)() = nullptr;
    void (*retro_set_environment)(retro_environment_t) = nullptr;
    bool (*retro_load_game)(const struct retro_game_info*) = nullptr;
};
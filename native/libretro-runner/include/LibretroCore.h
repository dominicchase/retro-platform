#pragma once

#include "libretro.h"
#include "CoreLoader.h"
#include <string>
#include <vector>

class LibretroCore
{
public:
    bool load(CoreLoader &loader);

    void init();

    bool loadGame(const std::string &path);

    void runFrame();

    void shutdown();

private:
    void (*retro_init)() = nullptr;

    void (*retro_set_environment)(
        retro_environment_t) = nullptr;

    void (*retro_set_video_refresh)(
        retro_video_refresh_t) = nullptr;

    void (*retro_set_audio_sample)(
        retro_audio_sample_t) = nullptr;

    void (*retro_set_audio_sample_batch)(
        retro_audio_sample_batch_t) = nullptr;

    void (*retro_set_input_poll)(
        retro_input_poll_t) = nullptr;

    void (*retro_set_input_state)(
        retro_input_state_t) = nullptr;

    bool (*retro_load_game)(
        const retro_game_info *) = nullptr;

    void (*retro_get_system_info)(
        retro_system_info *) = nullptr;

    void (*retro_get_system_av_info)(
        retro_system_av_info *) = nullptr;

    std::vector<unsigned char> romData;
};
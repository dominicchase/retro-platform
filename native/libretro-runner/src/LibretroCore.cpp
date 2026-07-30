#include <iostream>
#include <fstream>
#include <vector>

#include "LibretroCore.h"
#include "AudioManager.h"
#include "VideoRenderer.h"
#include "InputManager.h"

LibretroCore *g_core = nullptr;

bool environment_callback(unsigned cmd, void *data)
{
    switch (cmd)
    {
    case RETRO_ENVIRONMENT_SET_PIXEL_FORMAT:
        std::cout << "Set pixel format\n";
        return true;

    case RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY:
        std::cout << "Get system directory\n";
        return true;

    default:
        return false;
    }
}

void video_callback(
    const void *data,
    unsigned width,
    unsigned height,
    size_t pitch)
{
    if (g_core)
    {
        g_core->submitVideoFrame(
            data,
            width,
            height,
            pitch);
    }
}

void LibretroCore::submitVideoFrame(
    const void *data,
    unsigned width,
    unsigned height,
    size_t pitch)
{
    if (!videoRenderer)
    {
        return;
    }

    videoRenderer->setFrame(
        data,
        width,
        height,
        pitch);
}

void audio_sample_callback(
    int16_t left,
    int16_t right)
{
    // TODO: handle audio later
}

size_t audio_batch_callback(
    const int16_t *data,
    size_t frames)
{
    if (!g_core)
    {
        return frames;
    }

    g_core->audioBatch(
        data,
        frames);

    return frames;
}

void input_poll_callback()
{
    // TODO: poll controller later
}

int16_t input_state_callback(
    unsigned port,
    unsigned device,
    unsigned index,
    unsigned id)
{
    if (!g_core)
    {
        return 0;
    }

    return g_core->inputState(
        port,
        device,
        index,
        id);
}

bool LibretroCore::load(CoreLoader &loader)
{
    retro_init =
        reinterpret_cast<void (*)()>(
            loader.getFunction("retro_init"));

    retro_deinit =
        reinterpret_cast<void (*)()>(
            loader.getFunction("retro_deinit"));

    retro_set_environment =
        reinterpret_cast<void (*)(retro_environment_t)>(
            loader.getFunction("retro_set_environment"));

    retro_set_video_refresh =
        reinterpret_cast<void (*)(retro_video_refresh_t)>(
            loader.getFunction("retro_set_video_refresh"));

    retro_set_audio_sample =
        reinterpret_cast<void (*)(retro_audio_sample_t)>(
            loader.getFunction("retro_set_audio_sample"));

    retro_set_audio_sample_batch =
        reinterpret_cast<void (*)(retro_audio_sample_batch_t)>(
            loader.getFunction("retro_set_audio_sample_batch"));

    retro_set_input_poll =
        reinterpret_cast<void (*)(retro_input_poll_t)>(
            loader.getFunction("retro_set_input_poll"));

    retro_set_input_state =
        reinterpret_cast<void (*)(retro_input_state_t)>(
            loader.getFunction("retro_set_input_state"));

    retro_load_game =
        reinterpret_cast<bool (*)(const retro_game_info *)>(
            loader.getFunction("retro_load_game"));

    retro_run =
        reinterpret_cast<void (*)()>(
            loader.getFunction("retro_run"));

    retro_get_system_info =
        reinterpret_cast<void (*)(retro_system_info *)>(
            loader.getFunction("retro_get_system_info"));

    retro_get_system_av_info =
        reinterpret_cast<void (*)(retro_system_av_info *)>(
            loader.getFunction("retro_get_system_av_info"));

    if (!retro_init ||
        !retro_deinit ||
        !retro_set_environment ||
        !retro_set_video_refresh ||
        !retro_set_audio_sample ||
        !retro_set_audio_sample_batch ||
        !retro_set_input_poll ||
        !retro_set_input_state ||
        !retro_load_game ||
        !retro_run ||
        !retro_get_system_info ||
        !retro_get_system_av_info)
    {
        std::cout << "Failed to load libretro functions\n";
        return false;
    }

    return true;
}

void LibretroCore::init()
{
    g_core = this;

    retro_set_environment(environment_callback);

    retro_set_video_refresh(video_callback);

    retro_set_audio_sample(audio_sample_callback);

    retro_set_audio_sample_batch(audio_batch_callback);

    retro_set_input_poll(input_poll_callback);

    retro_set_input_state(input_state_callback);

    std::cout << "Calling retro_init...\n";

    retro_init();

    std::cout << "Core initialized\n";
}

bool LibretroCore::loadGame(const std::string &path)
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file)
    {
        std::cout << "Failed to open ROM\n";
        return false;
    }

    auto size = file.tellg();

    romData.resize(size);

    file.seekg(0, std::ios::beg);

    file.read(
        reinterpret_cast<char *>(romData.data()),
        size);

    retro_game_info gameInfo{};

    gameInfo.path = path.c_str();
    gameInfo.data = romData.data();
    gameInfo.size = romData.size();

    std::cout << "Loading ROM: "
              << gameInfo.path
              << std::endl;

    std::cout << "ROM size: "
              << gameInfo.size
              << " bytes\n";

    bool result = retro_load_game(&gameInfo);

    std::cout << "retro_load_game returned: "
              << result
              << std::endl;

    return result;
}

void LibretroCore::runFrame()
{
    retro_run();
}

void LibretroCore::setInputManager(InputManager *input)
{
    inputManager = input;
}

int16_t LibretroCore::inputState(
    unsigned port,
    unsigned device,
    unsigned index,
    unsigned id)
{
    if (!inputManager)
    {
        return 0;
    }

    return inputManager->getButtonState(id);
}

void LibretroCore::setAudioManager(AudioManager *audio)
{
    audioManager = audio;
}

void LibretroCore::audioBatch(
    const int16_t *data,
    size_t frames)
{
    if (!audioManager)
    {
        return;
    }

    audioManager->playSamples(
        data,
        frames);
}

double LibretroCore::getFPS()
{
    retro_system_av_info info{};

    retro_get_system_av_info(&info);

    return info.timing.fps;
}

void LibretroCore::shutdown()
{
    if (retro_deinit)
    {
        retro_deinit();
    }
}

void LibretroCore::setVideoRenderer(
    VideoRenderer *video)
{
    videoRenderer = video;
}
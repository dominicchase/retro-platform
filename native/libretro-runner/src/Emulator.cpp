#include <iostream>
#include <filesystem>
#include <SDL2/SDL.h>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Emulator.h"

bool Emulator::init(
    const char *corePath,
    const char *romPath)
{
    if (SDL_Init(
            SDL_INIT_VIDEO |
            SDL_INIT_AUDIO |
            SDL_INIT_GAMECONTROLLER) != 0)
    {
        std::cout
            << "SDL init failed: "
            << SDL_GetError()
            << std::endl;

        return false;
    }

    if (!saveManager.init())
    {
        std::cout
            << "Save manager initialization failed\n";

        return false;
    }

    if (!video.init())
    {
        std::cout
            << "Video initialization failed\n";

        shutdown();
        return false;
    }

    if (!audio.init())
    {
        std::cout
            << "Audio initialization failed\n";

        shutdown();
        return false;
    }

    if (!loader.load(corePath))
    {
        std::cout
            << "Failed to load core DLL\n";

        shutdown();
        return false;
    }

    if (!core.load(loader))
    {
        std::cout
            << "Failed to load libretro functions\n";

        shutdown();
        return false;
    }

    core.setAudioManager(&audio);

    core.setVideoRenderer(&video);

    core.setInputManager(&input);

    core.init();

    if (!core.loadGame(romPath))
    {
        std::cout
            << "Failed to load ROM\n";

        shutdown();
        return false;
    }

    std::filesystem::path path(romPath);

    state.currentGameName = path.stem().string();

    std::cout
        << "Game name: "
        << state.currentGameName
        << std::endl;

    auto slots =
        saveManager.getSlots(state.currentGameName);

    for (auto &slot : slots)
    {
        std::cout
            << "Slot "
            << slot.slotNumber
            << ": "
            << (slot.exists ? "USED" : "EMPTY");

        if (slot.exists)
        {
            std::cout
                << "\n   Saved: "
                << slot.metadata.date
                << " "
                << slot.metadata.time;
        }

        std::cout << "\n";
    }

    limiter.setFPS(
        core.getFPS());

    running = true;

    return true;
}

void Emulator::run()
{
    while (running)
    {
        running =
            video.processEvents();

        input.update();

        if (input.pausePressed())
        {
            if (state.runtimeState == RuntimeState::Running)
            {
                state.runtimeState = RuntimeState::Paused;
                std::cout << "Paused\n";
            }
            else if (state.runtimeState == RuntimeState::Paused)
            {
                state.runtimeState = RuntimeState::Running;
                std::cout << "Resumed\n";
            }
        }

        if (state.runtimeState == RuntimeState::Paused &&
            input.menuPressed())
        {
            state.runtimeState = RuntimeState::SaveMenu;

            std::cout << "Save Menu Opened\n";
        }

        switch (state.runtimeState)
        {
        case RuntimeState::Running:
            core.runFrame();
            break;

        case RuntimeState::Paused:
            break;

        case RuntimeState::SaveMenu:
            updateSaveMenu();

            if (input.pausePressed())
            {
                state.runtimeState = RuntimeState::Paused;
                std::cout << "Save Menu Closed\n";
            }

            break;
        }

        video.render();

        limiter.wait();

        input.endFrame();
    }
}

void Emulator::shutdown()
{
    video.shutdown();

    audio.shutdown();

    core.shutdown();

    SDL_Quit();
}

void Emulator::saveTestState()
{
    std::vector<uint8_t> buffer;

    if (!core.saveState(buffer))
    {
        std::cout << "Save failed\n";
        return;
    }

    if (saveManager.saveState(
            state.currentGameName,
            getSaveFilename(state.currentSaveSlot),
            buffer))
    {
        SaveMetadata metadata;

        metadata.slotNumber =
            state.currentSaveSlot;

        metadata.gameName =
            state.currentGameName;

        auto now =
            std::chrono::system_clock::now();

        auto time =
            std::chrono::system_clock::to_time_t(now);

        std::tm local{};

        localtime_s(
            &local,
            &time);

        std::stringstream date;
        date << std::put_time(
            &local,
            "%m/%d/%Y");

        std::stringstream clock;
        clock << std::put_time(
            &local,
            "%I:%M %p");

        metadata.date = date.str();
        metadata.time = clock.str();

        saveManager.saveMetadata(metadata);

        std::cout << "State saved!\n";

        auto slots =
            saveManager.getSlots(state.currentGameName);

        for (auto &slot : slots)
        {
            std::cout
                << "Slot "
                << slot.slotNumber
                << ": "
                << (slot.exists ? "USED" : "EMPTY");

            if (slot.exists)
            {
                std::cout
                    << "\n   Saved: "
                    << slot.metadata.date
                    << " "
                    << slot.metadata.time;
            }

            std::cout << "\n";
        }
    }
    else
    {
        std::cout << "Failed writing save file\n";
    }
}

void Emulator::loadTestState()
{
    std::vector<uint8_t> buffer;

    if (!saveManager.loadState(
            state.currentGameName,
            getSaveFilename(state.currentSaveSlot),
            buffer))
    {
        std::cout << "Failed reading save file\n";
        return;
    }

    if (core.loadState(buffer))
    {
        std::cout << "State loaded!\n";
    }
    else
    {
        std::cout << "Load failed\n";
    }
}

std::string Emulator::getSaveFilename(int slot) const
{
    return state.currentGameName +
           ".slot" +
           std::to_string(slot);
}

void Emulator::changeSaveSlot(int amount)
{
    state.currentSaveSlot += amount;

    if (state.currentSaveSlot < 0)
    {
        state.currentSaveSlot = 9;
    }

    if (state.currentSaveSlot > 9)
    {
        state.currentSaveSlot = 0;
    }

    std::cout
        << "Current save slot: "
        << state.currentSaveSlot
        << std::endl;
}

void Emulator::updateSaveMenu()
{
    if (input.nextSlotPressed())
    {
        changeSaveSlot(1);
    }

    if (input.previousSlotPressed())
    {
        changeSaveSlot(-1);
    }

    if (input.savePressed())
    {
        saveTestState();
    }

    if (input.loadPressed())
    {
        loadTestState();
    }
}
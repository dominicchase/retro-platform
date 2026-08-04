#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

#include "SaveManager.h"

bool SaveManager::init()
{
    try
    {
        std::filesystem::create_directories(
            saveDirectory);
    }
    catch (const std::exception &e)
    {
        std::cout
            << "Failed creating save directory: "
            << e.what()
            << std::endl;

        return false;
    }

    return true;
}

bool SaveManager::saveState(
    const std::string &filename,
    const std::vector<uint8_t> &buffer)
{
    std::ofstream file(
        saveDirectory + filename,
        std::ios::binary);

    if (!file)
    {
        return false;
    }

    file.write(
        reinterpret_cast<const char *>(buffer.data()),
        buffer.size());

    return true;
}

bool SaveManager::loadState(
    const std::string &filename,
    std::vector<uint8_t> &buffer)
{
    std::ifstream file(
        saveDirectory + filename,
        std::ios::binary | std::ios::ate);

    if (!file)
    {
        return false;
    }

    auto size = file.tellg();

    buffer.resize(size);

    file.seekg(0);

    file.read(
        reinterpret_cast<char *>(buffer.data()),
        size);

    return true;
}

std::vector<SaveSlot> SaveManager::getSlots(
    const std::string &gameName)
{
    std::vector<SaveSlot> slots;

    for (int i = 0; i < 10; i++)
    {
        std::string filename =
            gameName +
            ".slot" +
            std::to_string(i);

        std::filesystem::path path =
            saveDirectory + filename;

        SaveSlot slot;

        slot.slotNumber = i;

        slot.exists =
            std::filesystem::exists(path);

        if (slot.exists)
        {
            slot.modifiedTime =
                std::filesystem::last_write_time(path);
        }

        slot.filename = filename;

        slots.push_back(slot);
    }

    return slots;
}

std::string SaveManager::getSaveTime(
    const SaveSlot &slot)
{
    if (!slot.exists)
    {
        return "";
    }

    auto systemTime =
        std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            slot.modifiedTime -
            std::filesystem::file_time_type::clock::now() +
            std::chrono::system_clock::now());

    auto time =
        std::chrono::system_clock::to_time_t(systemTime);

    std::stringstream stream;

    stream
        << std::put_time(
               std::localtime(&time),
               "%Y-%m-%d %H:%M:%S");

    return stream.str();
}
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
            saveRoot);
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
    const std::string &gameName,
    const std::string &filename,
    const std::vector<uint8_t> &buffer)
{
    std::string directory =
        getGameDirectory(gameName);

    std::filesystem::create_directories(
        directory);

    std::ofstream file(
        directory + filename,
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
    const std::string &gameName,
    const std::string &filename,
    std::vector<uint8_t> &buffer)
{
    std::ifstream file(
        getGameDirectory(gameName) + filename,
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
            getGameDirectory(gameName) + filename;

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

bool SaveManager::saveMetadata(
    const SaveMetadata &metadata)
{
    std::ofstream file(
        getMetadataFilename(
            metadata.gameName,
            metadata.slotNumber));

    if (!file)
    {
        return false;
    }

    file << "game="
         << metadata.gameName
         << "\n";

    file << "slot="
         << metadata.slotNumber
         << "\n";

    file << "date="
         << metadata.date
         << "\n";

    file << "time="
         << metadata.time
         << "\n";

    return true;
}

std::string SaveManager::getGameDirectory(
    const std::string &gameName) const
{
    return saveRoot + gameName + "/";
}

std::string SaveManager::getMetadataFilename(
    const std::string &gameName,
    int slot) const
{
    return getGameDirectory(gameName) +
           gameName +
           ".slot" +
           std::to_string(slot) +
           ".meta";
}
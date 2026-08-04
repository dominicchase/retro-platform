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
            slot.metadata =
                loadMetadata(
                    gameName,
                    i);
        }

        slot.filename = filename;

        slots.push_back(slot);
    }

    return slots;
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

SaveMetadata SaveManager::loadMetadata(
    const std::string &gameName,
    int slot)
{
    SaveMetadata metadata;

    metadata.slotNumber = slot;
    metadata.gameName = gameName;

    std::ifstream file(
        getMetadataFilename(
            gameName,
            slot));

    if (!file)
    {
        return metadata;
    }

    std::string line;

    while (std::getline(file, line))
    {
        auto separator =
            line.find('=');

        if (separator == std::string::npos)
        {
            continue;
        }

        auto key =
            line.substr(
                0,
                separator);

        auto value =
            line.substr(
                separator + 1);

        if (key == "date")
        {
            metadata.date = value;
        }

        if (key == "time")
        {
            metadata.time = value;
        }
    }

    return metadata;
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
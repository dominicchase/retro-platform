#include <iostream>
#include <fstream>
#include <filesystem>

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
#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <filesystem>

struct SaveSlot
{
    int slotNumber;
    bool exists;
    std::string filename;
    std::filesystem::file_time_type modifiedTime;
};

class SaveManager
{
public:
    bool init();

    bool saveState(
        const std::string &filename,
        const std::vector<uint8_t> &buffer);

    bool loadState(
        const std::string &filename,
        std::vector<uint8_t> &buffer);

    std::vector<SaveSlot> getSlots(
        const std::string &gameName);

    std::string getSaveTime(
        const SaveSlot &slot);

private:
    std::string saveDirectory = "saves/states/";
};
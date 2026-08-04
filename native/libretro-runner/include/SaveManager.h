#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <filesystem>

struct SaveMetadata
{
    int slotNumber;
    std::string gameName;
    std::string date;
    std::string time;
};

struct SaveSlot
{
    int slotNumber;
    bool exists;
    std::string filename;
    std::filesystem::file_time_type modifiedTime;
    SaveMetadata metadata;
};

class SaveManager
{
public:
    bool init();

    bool saveState(
        const std::string &gameName,
        const std::string &filename,
        const std::vector<uint8_t> &buffer);

    bool loadState(
        const std::string &gameName,
        const std::string &filename,
        std::vector<uint8_t> &buffer);

    std::vector<SaveSlot> getSlots(
        const std::string &gameName);

    std::string getSaveTime(
        const SaveSlot &slot);

    bool saveMetadata(
        const SaveMetadata &metadata);

    SaveMetadata loadMetadata(
        const std::string &gameName,
        int slot);

private:
    std::string saveRoot = "saves/";

    std::string getGameDirectory(
        const std::string &gameName) const;

    std::string getMetadataFilename(
        const std::string &gameName,
        int slot) const;
};
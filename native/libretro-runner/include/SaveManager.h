#pragma once

#include <string>
#include <vector>
#include <cstdint>

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

private:
    std::string saveDirectory = "saves/states/";
};
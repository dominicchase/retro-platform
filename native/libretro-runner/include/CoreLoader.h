#pragma once

#include <windows.h>
#include <string>

class CoreLoader
{
public:
    bool load(const std::string& path);
    void* getFunction(const char* name);

private:
    HMODULE handle = nullptr;

};
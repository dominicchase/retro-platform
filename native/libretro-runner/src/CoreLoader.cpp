#include "CoreLoader.h"
#include <iostream>

bool CoreLoader::load(const std::string &path)
{
    if (handle)
    {
        FreeLibrary(handle);
        handle = nullptr;
    }

    handle = LoadLibraryA(path.c_str());

    if (!handle)
    {
        std::cerr
            << "Failed to load core. Error: "
            << GetLastError()
            << "\n";
        return false;
    }

    return true;
}

void *CoreLoader::getFunction(const char *name)
{
    return reinterpret_cast<void *>(GetProcAddress(handle, name));
}

CoreLoader::~CoreLoader()
{
    if (handle)
    {
        FreeLibrary(handle);
        handle = nullptr;
    }
}
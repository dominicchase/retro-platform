cmake_minimum_required(VERSION 3.20)

project(libretro-runner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(libretro-runner
    src/main.cpp
    src/CoreLoader.cpp
    src/LibretroCore.cpp
)

target_include_directories(libretro-runner PRIVATE
    include
)
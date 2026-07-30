cmake_minimum_required(VERSION 3.20)

project(libretro-runner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG REQUIRED)

add_executable(libretro-runner
    src/main.cpp
    src/CoreLoader.cpp
    src/LibretroCore.cpp
    src/VideoRenderer.cpp
)

target_include_directories(libretro-runner PRIVATE
    include
)

target_link_libraries(libretro-runner PRIVATE
    SDL2::SDL2
)
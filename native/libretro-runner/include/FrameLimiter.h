#pragma once

#include <chrono>

class FrameLimiter
{
public:
    void setFPS(double fps);

    void wait();

private:
    double frameDuration = 16.666;

    std::chrono::steady_clock::time_point nextFrame;
};
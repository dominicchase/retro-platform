#include "FrameLimiter.h"
#include <thread>

void FrameLimiter::setFPS(double fps)
{
    frameDuration = 1000.0 / fps;

    nextFrame =
        std::chrono::steady_clock::now();
}

void FrameLimiter::wait()
{
    auto now =
        std::chrono::steady_clock::now();

    auto frameTime =
        std::chrono::duration_cast<std::chrono::steady_clock::duration>(
            std::chrono::duration<double, std::milli>(
                frameDuration));

    nextFrame += frameTime;

    // We fell too far behind.
    // Reset instead of trying to catch up.
    if (now > nextFrame + frameTime * 5)
    {
        nextFrame = now;
    }

    if (nextFrame > now)
    {
        std::this_thread::sleep_until(nextFrame);
    }
}
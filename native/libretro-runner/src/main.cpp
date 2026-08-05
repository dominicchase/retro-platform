#define SDL_MAIN_HANDLED

#include "EmulatorRunner.h"
#include "EmulatorController.h"
#include "EmulatorBridge.h"

#include <iostream>

int main(int argc, char *argv[])
{

    EmulatorRunner runner;

    runner.start(
        argv[1],
        argv[2]);

    runner.stop();

    return 0;
}
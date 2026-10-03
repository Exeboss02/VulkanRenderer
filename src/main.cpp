#include <iostream>
#include <string>
#include <SDL3/SDL_main.h>
#include "engine.h"

int main(int argc, char*argv[])
{
    Engine engine;
    if(engine.Initialize(1280, 720))
    {
        engine.Run();
    }

    std::string test = "test";
    std::cout << test << std::endl;

    engine.ShutDown();

    return 0;
}
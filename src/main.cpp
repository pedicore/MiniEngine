#define SDL_MAIN_HANDLED

#include "Engine.h"
#include <iostream>

using namespace std;

int main()
{
    Engine engine;

    if (!engine.init())
    {
        cout << "Engine initialization failed\n";
        return 1;
    }

    while (engine.isRunning())
    {
        engine.handleEvents();
        engine.update();
        engine.render();
    }

    

    return 0;
}
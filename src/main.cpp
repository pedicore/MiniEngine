#define SDL_MAIN_HANDLED

#include "Engine.h"

int main()
{
    Engine engine;

    if (!engine.init())
        return 1;

    while (engine.isRunning())
    {
        engine.handleEvents();
        engine.update();
        engine.render();
    }

    return 0;
}
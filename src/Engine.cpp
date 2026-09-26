#include "Engine.h"
#include <iostream>

using namespace std;



bool Engine::init()
{
    // SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cout << SDL_GetError() << '\n';
        return false;
    }

    // Window
    window = SDL_CreateWindow(
        "Mini Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        cout << SDL_GetError() << '\n';
        SDL_Quit();
        return false;
    }

    // Renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (renderer == nullptr)
    {
        cout << SDL_GetError() << '\n';

        SDL_DestroyWindow(window);
        SDL_Quit();

        return false;
    }

    // Rectangle
    x = 100.0f;
    y = 150.0f;
    speed = 200.0f;

    rect.x = 100;
    rect.y = 150;
    rect.w = 200;
    rect.h = 100;

    // Time
    lastTime = SDL_GetTicks();

    running = true;

    return true;
}

bool Engine::isRunning() const
{
    return running;
}

void Engine::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
}

void Engine::update()
{
    // Delta Time
    Uint32 currentTime = SDL_GetTicks();
    Uint32 deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    float deltaSeconds = deltaTime / 1000.0f;

    // Keyboard
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_RIGHT])
    {
        x += speed * deltaSeconds;
    }

    if (keyboardState[SDL_SCANCODE_LEFT])
    {
        x -= speed * deltaSeconds;
    }

    if (keyboardState[SDL_SCANCODE_UP])
    {
        y -= speed * deltaSeconds;
    }

    if (keyboardState[SDL_SCANCODE_DOWN])
    {
        y += speed * deltaSeconds;
    }

    // Window boundaries
    if (x < 0)
    x = 0;

    if (x > WINDOW_WIDTH - rect.w)
        x = WINDOW_WIDTH - rect.w;

    if (y < 0)
        y = 0;

    if (y > WINDOW_HEIGHT - rect.h)
        y = WINDOW_HEIGHT - rect.h;

    // float position -> SDL_Rect position
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
}

void Engine::render()
{
    // Background
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    // Rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Show frame
    SDL_RenderPresent(renderer);
}

void Engine::clean()
{
    
    
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();

    running = false;
    
}
Engine::~Engine()
{
    clean();
}
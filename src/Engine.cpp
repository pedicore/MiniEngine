#include "Engine.h"
#include <iostream>

Engine::Engine()
{
}

Engine::~Engine()
{
    clean();
}

bool Engine::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL Init Error: "
                  << SDL_GetError() << '\n';

        return false;
    }

    window = SDL_CreateWindow(
        "MiniEngine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        std::cout << "Window Error: "
                  << SDL_GetError() << '\n';

        clean();
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!renderer)
    {
        std::cout << "Renderer Error: "
                  << SDL_GetError() << '\n';

        clean();
        return false;
    }

    // Load Player Texture
    if (!textureManager.load(
            renderer,
            "player",
            "assets/player.bmp"
        ))
    {
        clean();
        return false;
    }

    // Create Player after Texture exists
    player = std::make_unique<Player>(
        100.0f,
        100.0f,
        300.0f,
        textureManager.get("player")
    );

    running = true;
    lastTime = SDL_GetTicks();

    return true;
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
    Uint32 currentTime = SDL_GetTicks();

    float deltaTime =
        (currentTime - lastTime) / 1000.0f;

    lastTime = currentTime;

    const Uint8* keyboardState =
        SDL_GetKeyboardState(nullptr);

    input.moveRight =
        keyboardState[SDL_SCANCODE_RIGHT];

    input.moveLeft =
        keyboardState[SDL_SCANCODE_LEFT];

    input.moveUp =
        keyboardState[SDL_SCANCODE_UP];

    input.moveDown =
        keyboardState[SDL_SCANCODE_DOWN];

    if (player)
    {
        player->update(
            deltaTime,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            input
        );
    }
}

void Engine::render()
{
    SDL_SetRenderDrawColor(
        renderer,
        20, 20, 20, 255
    );

    SDL_RenderClear(renderer);

    if (player)
    {
        player->render(renderer);
    }

    SDL_RenderPresent(renderer);
}

bool Engine::isRunning() const
{
    return running;
}

void Engine::clean()
{
    // Player uses the texture,
    // so destroy Player first.
    player.reset();

    // Then destroy textures.
    textureManager.clear();

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();

    running = false;
}
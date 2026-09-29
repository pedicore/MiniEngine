#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Player.h"
#include "InputState.h"
#include "TextureManager.h"

class Engine
{
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool running = false;

    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;

    Uint32 lastTime = 0;

    InputState input;

    TextureManager textureManager;

    std::unique_ptr<Player> player;

    void clean();

public:
    Engine();
    ~Engine();

    bool init();

    void handleEvents();
    void update();
    void render();

    bool isRunning() const;
};
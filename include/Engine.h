#pragma once

#include <SDL2/SDL.h>

class Engine
{
private:
    private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool running = false;


    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;

    SDL_Rect rect;

    float x;
    float y;
    float speed;

    Uint32 lastTime;
    void clean();
public:
    bool init();
    void handleEvents();
    void update();
    void render();
    

    bool isRunning() const;
    ~Engine();
};
#pragma once

#include <SDL2/SDL.h>
#include "InputState.h"

class Player
{
private:
    SDL_Rect rect;

    float x;
    float y;
    float speed;

    SDL_Texture* texture = nullptr;

public:
    Player(
        float startX,
        float startY,
        float moveSpeed,
        SDL_Texture* playerTexture
    );

    void update(
        float deltaTime,
        int windowWidth,
        int windowHeight,
        const InputState& input
    );

    void render(SDL_Renderer* renderer);
};
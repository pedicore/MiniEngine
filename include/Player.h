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

public:
    Player(float startX, float startY, float moveSpeed);

    void update(
        float deltaTime,
        int windowWidth,
        int windowHeight,
        const InputState& input
    );

    void render(SDL_Renderer* renderer);
};
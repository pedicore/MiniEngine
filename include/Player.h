#pragma once

#include <SDL2/SDL.h>
#include "InputState.h"
#include "GameObject.h"
class Player: public GameObject
{
private:
    

    float x;
    float y;
    float speed;
    float scale = 1.0f;
    

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

    void render(SDL_Renderer* renderer) override;
};
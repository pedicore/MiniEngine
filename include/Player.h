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
    InputState currentInput{};
    int currentWindowWidth = 0;
    int currentWindowHeight = 0;
    

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

    void setInput(
    const InputState& newInput,
    int width,
    int height
    );
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
};
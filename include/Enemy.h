#pragma once
#include "GameObject.h"

class Enemy final : public GameObject {
    SDL_Rect sourceRect{};
    int currentFrame = 0;
    float animationTimer = 0.0f;
    float frameDuration = 0.15f;
    static constexpr int frameCount = 4;
    float positionX = 0.0f;
    float moveSpeed = 100.0f;
    int direction = 1;
public:
    Enemy(int startX, int startY, SDL_Texture* enemyTexture, float animationSpeed);
    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;
    void keepInBounds(int width);
};

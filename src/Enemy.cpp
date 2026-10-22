#include "Enemy.h"
#include <algorithm>

Enemy::Enemy(int startX, int startY, SDL_Texture* enemyTexture, float animationSpeed)
    : GameObject(enemyTexture), frameDuration(animationSpeed > 0 ? animationSpeed : 0.15f), positionX(static_cast<float>(startX)) {
    rect.x = startX;
    rect.y = startY;
    int w = 0, h = 0;
    if (texture && SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) == 0) {
        sourceRect = {0, 0, w / frameCount, h};
        rect.w = sourceRect.w;
        rect.h = sourceRect.h;
    } else {
        rect.w = 32;
        rect.h = 32;
    }
}

void Enemy::render(SDL_Renderer* renderer) {
    if (texture) SDL_RenderCopy(renderer, texture, &sourceRect, &rect);
}

void Enemy::update(float dt) {
    positionX += moveSpeed * direction * dt;
    rect.x = static_cast<int>(positionX);
    animationTimer += dt;
    while (animationTimer >= frameDuration) {
        animationTimer -= frameDuration;
        currentFrame = (currentFrame + 1) % frameCount;
    }
    sourceRect.x = currentFrame * sourceRect.w;
}

void Enemy::keepInBounds(int width) {
    if (rect.x < 0) { positionX = 0; direction = 1; }
    if (rect.x + rect.w > width) { positionX = static_cast<float>(width - rect.w); direction = -1; }
    rect.x = static_cast<int>(positionX);
}

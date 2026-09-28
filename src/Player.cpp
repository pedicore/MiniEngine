#include "Player.h"

Player::Player(float startX, float startY, float moveSpeed)
    : x(startX),
      y(startY),
      speed(moveSpeed)
{
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    rect.w = 50;
    rect.h = 50;
}

void Player::update(
    float deltaTime,
    int windowWidth,
    int windowHeight,
    const InputState& input
)
{
    if (input.moveRight)
        x += speed * deltaTime;

    if (input.moveLeft)
        x -= speed * deltaTime;

    if (input.moveUp)
        y -= speed * deltaTime;

    if (input.moveDown)
        y += speed * deltaTime;

    // Window boundaries
    if (x < 0)
        x = 0;

    if (x > windowWidth - rect.w)
        x = windowWidth - rect.w;

    if (y < 0)
        y = 0;

    if (y > windowHeight - rect.h)
        y = windowHeight - rect.h;

    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_RenderFillRect(renderer, &rect);
}
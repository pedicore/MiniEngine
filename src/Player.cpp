#include "Player.h"

Player::Player(
    float startX,
    float startY,
    float moveSpeed,
    SDL_Texture* playerTexture
)
    : x(startX),
      y(startY),
      speed(moveSpeed),
      texture(playerTexture)
{
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    rect.w = 64;
    rect.h = 64;
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
    if (texture)
    {
        SDL_RenderCopy(
            renderer,
            texture,
            nullptr,
            &rect
        );
    }
}
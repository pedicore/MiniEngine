#include "Player.h"
#include <iostream>
Player::Player(
    float startX,
    float startY,
    float moveSpeed,
    SDL_Texture* playerTexture
)
    :GameObject(playerTexture),
        x(startX),
        y(startY),
        speed(moveSpeed)
{
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    int textureWidth = 0;
    int textureHeight = 0;
    if (texture == nullptr)
    {
        std::cout << "Player texture is null\n";
        rect.w = 0;
        rect.h = 0;
        return;
    }
  if (SDL_QueryTexture(
        texture,
        nullptr,
        nullptr,
        &textureWidth,
        &textureHeight
    ) != 0)
{
    std::cout << "Failed to query texture: "
              << SDL_GetError() << '\n';
}

    std::cout << textureWidth << " x "
              << textureHeight << '\n';
    
    rect.w = static_cast<int>(textureWidth * scale);
    rect.h = static_cast<int>(textureHeight * scale);

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
void Player::update(float deltaTime)
{
    update(
        deltaTime,
        currentWindowWidth,
        currentWindowHeight,
        currentInput
    );
}

void Player::setInput(
    const InputState& newInput,
    int width,
    int height
)
{
    currentInput = newInput;
    currentWindowWidth = width;
    currentWindowHeight = height;
}
#pragma once
#include <SDL2/SDL.h>

class GameObject
{
protected:
SDL_Texture* texture = nullptr;
SDL_Rect rect;

public:


GameObject(SDL_Texture* objectTexture);
virtual void render(SDL_Renderer* renderer) = 0;
virtual void update(float deltaTime) = 0;
virtual ~GameObject() = default;

};
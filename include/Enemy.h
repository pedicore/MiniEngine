#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <string.h>


class Enemy {

private:

SDL_Rect rect;
SDL_Rect sourceRect;
SDL_Texture* texture = nullptr;
int currentFrame = 0;
float animationTimer = 0.0f;
float frameDuration = 0.15f;
const int frameCount = 4;

public:

Enemy(

    int startX,
    int startY,
    SDL_Texture* enemyTexture,
    float animationSpeed
    
);


void render(SDL_Renderer* renderer);
void update(float deltaTime);

};

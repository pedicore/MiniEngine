#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <string.h>


class Enemy {

private:

SDL_Rect rect;
SDL_Texture* texture = nullptr;
SDL_Rect sourceRect;
int currentFrame = 0;
int frameCount = 4;
float animationTimer = 0.0f;
float frameDuration = 0.15f;

public:

Enemy(

    int startX,
    int startY,
    SDL_Texture* enemyTexture
    
);


void render(SDL_Renderer* renderer);
void update(float deltaTime);

};

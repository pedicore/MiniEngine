#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <string.h>
#include "GameObject.h"


class Enemy: public GameObject {

private:


SDL_Rect sourceRect;

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


void render(SDL_Renderer* renderer) override;
void update(float deltaTime) override;

};

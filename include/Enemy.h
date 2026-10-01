#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <string.h>


class Enemy {

private:

SDL_Rect rect;
SDL_Texture* texture = nullptr;



public:

Enemy(

    int startX,
    int startY,
    SDL_Texture* enemyTexture
);


void render(SDL_Renderer* renderer);

};

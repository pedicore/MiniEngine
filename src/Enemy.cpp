#include "Enemy.h"
#include <iostream>

Enemy::Enemy(

    int startX,
    int startY,
    SDL_Texture* enemyTexture
)
:texture(enemyTexture)

{
    rect.x = startY ; 
    rect.y = startX ; 
    //texture

    int textureWidth = 0;
    int textureHeight = 0;

    SDL_QueryTexture(

   texture,
   nullptr,
   nullptr,
   &textureWidth,
   &textureHeight

   );
    rect.w = textureWidth;
    rect.h = textureHeight;
}

void Enemy::render(SDL_Renderer* renderer)
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



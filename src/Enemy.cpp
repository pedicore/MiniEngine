#include "Enemy.h"
#include <iostream>

Enemy::Enemy(

    int startX,
    int startY,
    SDL_Texture* enemyTexture,
    float animationSpeed
)   
:GameObject(enemyTexture), frameDuration(animationSpeed)

{
    if (frameDuration <= 0.0f)
    {
        frameDuration = 0.15f;
    }
    
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
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = textureWidth / frameCount;
    sourceRect.h = textureHeight;


    rect.w = textureWidth;
    rect.h = textureHeight;
    //temp
       

        sourceRect.x =
        currentFrame * sourceRect.w;
}

void Enemy::render(SDL_Renderer* renderer)
{
    if (texture)
    {
        SDL_RenderCopy(
            renderer,
            texture,
            &sourceRect,
            &rect
        );
    }

}

void Enemy::update(float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= frameDuration)
    {
        animationTimer -= frameDuration;
        animationTimer = 0.0f;

        currentFrame++;

        if (currentFrame >= frameCount)
        {
            currentFrame = 0;
        }

        sourceRect.x =
            currentFrame * sourceRect.w;
    }
}

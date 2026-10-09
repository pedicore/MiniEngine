#pragma once
#include <SDL2/SDL.h>

inline bool checkCollision(
    const SDL_Rect& a,
    const SDL_Rect& b 
)
{
    return  a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y;

    
}

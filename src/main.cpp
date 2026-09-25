#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

int main(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        
        cout<<SDL_GetError();
        return 1 ;

    }
    cout<<"SDL initialized successfully\n";
    SDL_Window* window = SDL_CreateWindow(

        "Mini Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN



    );
    if (window == nullptr)
    {
        cout<<SDL_GetError();
        SDL_Quit();
        return 1;

    }
    
    else{
        cout<<"Window created successfully";

    }
    
    
    bool running = true;
    SDL_Event event;

    SDL_Renderer* renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED
    );
    if (renderer == nullptr)
    {
        cout<<SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    Uint32 lastTime = SDL_GetTicks();

    float x = 100.0f;
    float speed = 200.0f;
    float y = 150.0f;

    SDL_Rect rect;
            rect.x = 100;
            rect.y = 150;
            rect.w = 200;
            rect.h = 100;




    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        float deltaSeconds = deltaTime / 1000.0f;
        // INPUT / EVENTS
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    // Right Arrow pressed
                    cout << "RIGHT\n";
                }
            }
        
        }
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        // UPDATE
        if (keyboardState[SDL_SCANCODE_RIGHT])
        {
            
            x += speed * deltaSeconds;
            
        }
        if (keyboardState[SDL_SCANCODE_LEFT])
        {
            
            x -= speed * deltaSeconds;
            
        }
        if (keyboardState[SDL_SCANCODE_UP])
        {
            
            y -= speed * deltaSeconds;
            
        }
        if (keyboardState[SDL_SCANCODE_DOWN])
        {
            
            y += speed * deltaSeconds;
            
        }
            if (x < 0)
            {
                x = 0;
            }

            if (x > 600)
            {
                x = 600;
            }

            if (y < 0)
            {
                y = 0;
            }

            if (y > 500)
            {
                y = 500;
            }
       //x += speed * deltaSeconds;
        rect.x = static_cast<int>(x);
        rect.y = static_cast<int>(y);
        //RENDER
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
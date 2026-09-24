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

    while (running)
    {
        // INPUT / EVENTS
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
        // UPDATE

        //RENDER
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
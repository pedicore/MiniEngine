#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

class TextureManager
{
private:
    std::unordered_map<std::string, SDL_Texture*> textures;

public:
    ~TextureManager();

    bool load(
        SDL_Renderer* renderer,
        const std::string& name,
        const std::string& filePath
    );

    SDL_Texture* get(const std::string& name);

    void clear();
};
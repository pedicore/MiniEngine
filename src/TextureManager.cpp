#include "TextureManager.h"
#include <iostream>

TextureManager::~TextureManager()
{
    clear();
}

bool TextureManager::load(
    SDL_Renderer* renderer,
    const std::string& name,
    const std::string& filePath
)
{
   
    if (textures.find(name) != textures.end())
    {
        return true;
    }

    SDL_Surface* surface =
        SDL_LoadBMP(filePath.c_str());

    if (!surface)
    {
        std::cout << "Failed to load image: "
                  << SDL_GetError() << '\n';

        return false;
    }

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(
            renderer,
            surface
        );

    SDL_FreeSurface(surface);

    if (!texture)
    {
        std::cout << "Failed to create texture: "
                  << SDL_GetError() << '\n';

        return false;
    }

    textures[name] = texture;

    return true;
}

SDL_Texture* TextureManager::get(
    const std::string& name
)
{
    auto it = textures.find(name);

    if (it == textures.end())
    {
        return nullptr;
    }

    return it->second;
}

void TextureManager::clear()
{
    for (auto& pair : textures)
    {
        SDL_DestroyTexture(pair.second);
    }

    textures.clear();
}
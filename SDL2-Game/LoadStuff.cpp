#include "LoadStuff.h"
#include <iostream>

// ========================================
// LOAD BMP TEXTURE (white = transparent)
// =======================================

SDL_Texture* LoadStuff::LoadPicture(
    const std::string& filePath,
    SDL_Renderer* renderer)
{

    // load BMP surface
    SDL_Surface* tempSurface = SDL_LoadBMP(filePath.c_str());

    if (!tempSurface)
    {
        std::cout << "ERROR failed to load image: " << filePath << std::endl;
        std::cout << "SDL error: " << SDL_GetError() << std::endl;
        return nullptr;

    }

    // make white colour transparent (255,255,255)
    SDL_SetColorKey(tempSurface, SDL_TRUE,
        SDL_MapRGB(tempSurface->format, 255, 255, 255));

    // create texture from surface (GPU memory)
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);


    // free temporary surface (no longer needed)
    SDL_FreeSurface(tempSurface);

    if (!newTexture)
    {
        std::cout << "ERROR: failed to create texture from: " << filePath << std::endl;

    }


    return newTexture;
}
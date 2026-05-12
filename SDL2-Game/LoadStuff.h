#pragma once

#include <SDL.h>
#include <string>

// ==========================================
// TEXTURE LOADER only BMP for now
// ==========================================

class LoadStuff
{

public:

    static SDL_Texture* LoadPicture(
        const std::string& filePath,
        SDL_Renderer* renderer

    );
};
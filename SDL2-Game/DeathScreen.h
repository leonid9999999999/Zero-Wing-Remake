#pragma once
#include <SDL.h>

// ===============
// DeathScreen
// =============
class DeathScreen
{
private:
    SDL_Texture* backgroundPic; // game over background image
    SDL_Texture* restartPic;   // button play again

    SDL_Texture* menuPic;   //button back to menu

    SDL_Rect restartButtonZone;   // x=550,y=500,w=500,h=150
    SDL_Rect menuButtonZone;      // x=550,y=700,w=500,h=150

public:
    DeathScreen();

    bool LoadAllPictures(SDL_Renderer* renderer);

    void HandleInput(SDL_Event& event, bool& needRestart, bool& backToMenu); // checks mouse clicks

    void Draw(SDL_Renderer* renderer);
    void DeleteTextures();
};
#pragma once

#include <SDL.h>

// ===========
// start screen
// ==============

class StartScreen
{

private:
    SDL_Texture* backgroundPic;  // menu background
    SDL_Texture* gameLogoPic;  // game logo

    SDL_Texture* startButtonPic; // start button
    SDL_Texture* exitButtonPic;// exit button

    SDL_Rect startButtonZone; // x=550,y=500,w=500,h=140
    SDL_Rect exitButtonZone;  // x=550,y=700,w=500,h=140

public:

    StartScreen();

    bool LoadAllPictures(SDL_Renderer* renderer);
    void HandleMenuInput(SDL_Event& event, bool& wantToPlay, bool& wantToExit); //mouse click detection
    void Draw(SDL_Renderer* renderer);

    void DeleteTextures();

};
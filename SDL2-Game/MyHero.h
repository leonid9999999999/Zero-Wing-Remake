#pragma once

#include <SDL.h>

// =========
// MY HERO
// ========

class MyHero
{
private:
    SDL_Texture* heroPic;    // ship sprite
    SDL_Rect heroPos;    // x,y,width=100,height=80

    int flySpeed;// 5 pixels per frame

    int healthPoints;  // starts at 3, game over at 0

public:

    MyHero();

    bool LoadHeroPicture(SDL_Renderer* renderer);
    void GetKeyboardInput(const Uint8* keys);   // WASD + arrow keys
    void Move();  // updates position, clamps to screen edges
    void Draw(SDL_Renderer* renderer);
    void DeleteTexture();

    SDL_Rect GetHeroPosition();
    void GetDamage(); // called when hit by enemy/bullet/rock

    int GetHealthLeft();
};
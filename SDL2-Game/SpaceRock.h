#pragma once

#include <SDL.h>

// =============
// space rock
// ===========
class SpaceRock
{
private:
    SDL_Texture* rockTexture;
    SDL_Rect rockRect;  // x,y,width=80,height=80
    int flySpeedX; // 4 pixels left per frame

    int flySpeedY;  // random: 0, +2, or -2
    bool isAlive; // false if off screen or destroyed

public:
    SpaceRock(int startX, int startY);   // spawns at right edge

    bool LoadPicture(SDL_Renderer* renderer);
    void Move();   // moves left, dies when x < -100

    void Draw(SDL_Renderer* renderer);

    SDL_Rect GetPosition();
    bool IsAlive();

    void Kill();     // called when hit by bullet or player
};
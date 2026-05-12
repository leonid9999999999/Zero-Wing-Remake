#pragma once

#include <SDL.h>


// ========
// PLAYER BULLET
// ============

class MyBullet
{
private:
    SDL_Texture* bulletPic;
    SDL_Rect bulletPos;  // x,y,width=40,height=20
    int flySpeed;   // 8 pixels per frame (flies right)
    bool isAlive;   // false when off screen or hit enemy


public:
    MyBullet(int startX, int startY);  // spawns from ship nose

    bool LoadBulletPicture(SDL_Renderer* renderer);
    void Fly(); // moves right, dies if x > 1600

    void Draw(SDL_Renderer* renderer);

    bool IsAlive();
    void Destroy();

    SDL_Rect GetBulletPosition();

};
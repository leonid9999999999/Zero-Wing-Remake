#pragma once
#include <SDL.h>

// ===============
// ENEMY BULLET
// ====================
class BadBullet
{
private:
    SDL_Texture* bulletPic;  // Might be nullptr if texture fails to load
    SDL_Rect bulletPos;  // x,y,width,height - width=35, height=20
    int flySpeed;    // 6 pixels per frame (slower than player bullet)
    bool isAlive; // false = off screen or hit something

public:
    BadBullet(int startX, int startY); // spawns at enemy position (x+? , y+25)

    bool LoadPicture(SDL_Renderer* renderer);  // loads enemy_projectile.bmp
    void Fly();  // moves left, dies if x < -width
    void Draw(SDL_Renderer* renderer);

    bool IsAlive();
    void Destroy();  // called when hits player or off screen
    SDL_Rect GetPosition();
};
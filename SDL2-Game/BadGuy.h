#pragma once
#include <SDL.h>

// ========================
// ENEMY MOVEMENT PATTERNS
// ========================
enum class MoveType
{
    ZigZag, // goes up and down, changes direction every ~40 frames
    Wave,  // sine wave motion based on X position
    Dive  // waits, dives down fast, then flies up slowly
};

// =============================
// REGULAR ENEMY (not the boss)
// =============================
class BadGuy
{
private:
    SDL_Texture* enemyPic;  // sprite image
    SDL_Rect enemyPos; // x,y,width=100,height=80

    int speedX;  // -2 (flies left)
    int speedY;   // used for ZigZag pattern

    int moveTimer;  // counts frames for pattern timing
    int shootCooldown;// counts frames until next shot
    int shootDelayTime;    // random between 90-210 frames

    MoveType currentMove;    // chosen randomly at spawn
    bool isGoingDown;   // used by ZigZag
    bool isAlive;          // false = dead, will be removed
    int spawnY;     // remembered Y position for Wave pattern


public:
    BadGuy(int startX, int startY);  // appears at right edge (X=1600)

    bool LoadPicture(SDL_Renderer* renderer);
    void Move();   // updates position based on currentMove
    bool ReadyToShoot();   // true if cooldown >= delay
    void ResetShootTimer();   // call after shooting, sets new random delay
    void Draw(SDL_Renderer* renderer);

    bool IsAlive();
    void Kill();
    SDL_Rect GetPosition();

};
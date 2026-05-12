#pragma once
#include <SDL.h>



// ==============
// Big Bad Guy
// ================
class BigBadGuy
{
private:
    SDL_Texture* bossPic;
    SDL_Rect bossPos;    // x=1300,y=450,width=250,height=200

    int hp;     // 20 hits to kill
    int moveCounter;       // for sine wave movement
    int reloadCounter;      // frames between shots
    int reloadTime;      // 120 frames = shoot every 2 seconds
    int attackTimer;      // counts phases of attack/reload
    int attackLength;        // 180 frames = 3 seconds of shooting
    int reloadLength;         // 480 frames = 8 seconds of cooldown
    bool readyToShoot;       // true = can shoot, false = reloading
    bool isAlive;      // false = dead or not spawned yet

public:
    BigBadGuy();

    bool LoadPicture(SDL_Renderer* renderer);
    void Update();      // sine wave movement + attack/reload phases
    void Draw(SDL_Renderer* renderer);

    bool IsAlive();
    void StartFight();    // called when player reaches 1500 points
    void GetHit();       // reduces hp by 1, kills boss if hp <= 0
    bool CanFire();       // true if readyToShoot AND reloadCounter >= reloadTime
    void ResetFireTimer();    // call after firing
    SDL_Rect GetPosition();
    int GetHealthPoints();
};
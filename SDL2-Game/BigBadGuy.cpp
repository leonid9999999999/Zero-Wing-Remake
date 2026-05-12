#include "BigBadGuy.h"
#include "LoadStuff.h"
#include <cmath>
#include <iostream>

// ==========+=
// CONSTRUCTOR
// ===========
BigBadGuy::BigBadGuy()
{
    bossPic = nullptr;

    bossPos.x = 1300;   // right side of screen
    bossPos.y = 450;   // centre-ish (1200/2 - 200/2 = 500? but 450 works)
    bossPos.w = 250;
    bossPos.h = 200;

    hp = 20;       // takes 20 hits to kill
    moveCounter = 0;
    reloadCounter = 0;
    reloadTime = 120;    // shoot every 2 seconds (120 frames)
    attackTimer = 0;
    attackLength = 180;  // attack for 3 seconds
    reloadLength = 480;   // reload for 8 seconds

    readyToShoot = true;
    isAlive = false;  // not active until wave 3
}

// ============
// LOAD TEXTURE
// ==========
bool BigBadGuy::LoadPicture(SDL_Renderer* renderer)
{
    bossPic = LoadStuff::LoadPicture("assets/textures/boss_enemy.bmp", renderer);
    return bossPic != nullptr;
}

// =======================================
// BOSS UPDATE (movement + attack phases)
// =====================================
void BigBadGuy::Update()
{
    if (!isAlive) return;

    // sinusoidal movement (smooth up and down)
    moveCounter++;
    bossPos.y = 450 + static_cast<int>(80 * sin(moveCounter * 0.015));

    reloadCounter++;
    attackTimer++;

    // attack / reload phase management
    if (readyToShoot)
    {
        // attacking phase
        if (attackTimer >= attackLength)
        {
            readyToShoot = false;
            attackTimer = 0;

        }
    }



    else
    {
        // reloading phase
        if (attackTimer >= reloadLength)

        {
            readyToShoot = true;
            attackTimer = 0;

        }




    }
}

// ==========
// DRAW BOSS
// ===========

void BigBadGuy::Draw(SDL_Renderer* renderer)
{
    if (isAlive && bossPic)
        SDL_RenderCopy(renderer, bossPic, nullptr, &bossPos);
}

bool BigBadGuy::IsAlive() { return isAlive; }
void BigBadGuy::StartFight() { isAlive = true; }

void BigBadGuy::GetHit()
{
    hp--;
    std::cout << "BOSS HIT! HP left: " << hp << std::endl;

    if (hp <= 0)
    {
        isAlive = false;
        std::cout << "BOSS DEFEATED!" << std::endl;


    }
}

bool BigBadGuy::CanFire() { return readyToShoot && reloadCounter >= reloadTime; }
void BigBadGuy::ResetFireTimer() { reloadCounter = 0; }
SDL_Rect BigBadGuy::GetPosition() { return bossPos; }
int BigBadGuy::GetHealthPoints() { return hp; }
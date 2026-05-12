#include "BadGuy.h"
#include "LoadStuff.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

// ==========================================
// CONSTRUCTOR
// ==========================================
BadGuy::BadGuy(int startX, int startY)
{
    enemyPic = nullptr;

    enemyPos.x = startX;
    enemyPos.y = startY;
    enemyPos.w = 100;
    enemyPos.h = 80;

    speedX = 2; // flies left
    speedY = 2;   // vertical speed (zigzag)
    moveTimer = 0;
    shootCooldown = 0;
    shootDelayTime = 90 + rand() % 120;   // random delay between 90-210 frames
    isGoingDown = true;
    isAlive = true;
    spawnY = startY; // remember for wave pattern

    // random movement pattern at spawn
    int randomPattern = rand() % 3;
    if (randomPattern == 0) currentMove = MoveType::ZigZag;
    else if (randomPattern == 1) currentMove = MoveType::Wave;
    else currentMove = MoveType::Dive;
}

// ============
// LOAD TEXTURE
// ============
bool BadGuy::LoadPicture(SDL_Renderer* renderer)
{
    enemyPic = LoadStuff::LoadPicture("assets/textures/enemy_ship.bmp", renderer);
    return enemyPic != nullptr;
}

// ==========================
// MOVE ENEMY (3 patterns)
// =======================
void BadGuy::Move()
{
    moveTimer++;
    shootCooldown++;
    enemyPos.x -= speedX; // always moving left

    switch (currentMove)
    {
    case MoveType::ZigZag:
        if (isGoingDown) enemyPos.y += speedY;
        else enemyPos.y -= speedY;
        // change direction every 40 frames

        if (moveTimer % 40 == 0) isGoingDown = !isGoingDown;
        break;

    case MoveType::Wave:

        // sine wave based on X position

        enemyPos.y = spawnY + static_cast<int>(50 * sin(enemyPos.x * 0.03));
        break;

    case MoveType::Dive:

        // phase 1: wait (0-60), phase 2: dive down (60-120), phase 3: fly up (120+)
        if (moveTimer >= 60 && moveTimer < 120) enemyPos.y += 4;
        else if (moveTimer >= 120) enemyPos.y -= 2;
        break;
    }

    // screen boundaries (keep enemy visible)
    if (enemyPos.y < 50) enemyPos.y = 50;
    if (enemyPos.y > 1050) enemyPos.y = 1050;
    // off screen left, kill it
    if (enemyPos.x < -enemyPos.w) isAlive = false;
}

// ==========
// SHOOTING
// =========
bool BadGuy::ReadyToShoot() { return shootCooldown >= shootDelayTime; }

void BadGuy::ResetShootTimer()
{
    shootCooldown = 0;
    shootDelayTime = 90 + rand() % 120; // new random delay (staggered firing)
}

// ======
// DRAW
// ======
void BadGuy::Draw(SDL_Renderer* renderer)
{
    if (enemyPic) SDL_RenderCopy(renderer, enemyPic, nullptr, &enemyPos);
}

bool BadGuy::IsAlive() { return isAlive; }
void BadGuy::Kill() { isAlive = false; }
SDL_Rect BadGuy::GetPosition() { return enemyPos; }
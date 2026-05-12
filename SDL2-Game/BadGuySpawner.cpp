#include "BadGuySpawner.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

// =============
// CONSTRUCTOR
// ============
BadGuySpawner::BadGuySpawner()
{
    spawnCooldown = 0;
    enemySpawnDelay = 400; // frames between spawns (was 220, changed to 400 for less enemies)
    canSpawnBadGuys = true;
}

// ===================================================
// UPDATE ALL ENEMIES (spawn + move + shoot + delete)
// =================================================
void BadGuySpawner::UpdateAllBadGuys(SDL_Renderer* renderer, BadBulletManager& enemyBullets)

{
    // SPAWN NEW ENEMIES
    spawnCooldown++;

    if (canSpawnBadGuys && spawnCooldown >= enemySpawnDelay)
    {
        int randomHeight = rand() % 900 + 100;   // range 100-1000 (avoid screen edges)
        BadGuy newBadGuy(1600, randomHeight); // spawn at right edge
        newBadGuy.LoadPicture(renderer);

        badGuys.push_back(newBadGuy);
        spawnCooldown = 0;
    }

    // MOVE AND SHOOT
    for (auto& badGuy : badGuys)
    {
        badGuy.Move();

        if (badGuy.ReadyToShoot())
        {
            SDL_Rect pos = badGuy.GetPosition();
            enemyBullets.AddNewBadBullet(pos.x, pos.y + 25, renderer);   // bullet from enemy center
            badGuy.ResetShootTimer();

        }


    }

    // REMOVE DEAD ENEMIES
    badGuys.erase(
        std::remove_if(badGuys.begin(), badGuys.end(),
            [](BadGuy& bg) { return !bg.IsAlive(); }),

        badGuys.end()
    );
}

// =================
// DRAW ALL ENEMIES
// ==================
void BadGuySpawner::DrawAllBadGuys(SDL_Renderer* renderer)
{
    for (auto& badGuy : badGuys)
        badGuy.Draw(renderer);

}
std::vector<BadGuy>& BadGuySpawner::GetAllBadGuys() { return badGuys; }

void BadGuySpawner::StopSpawningBadGuys() { canSpawnBadGuys = false; }
void BadGuySpawner::StartSpawningBadGuys() { canSpawnBadGuys = true; }
void BadGuySpawner::RemoveAllBadGuys() { badGuys.clear(); }
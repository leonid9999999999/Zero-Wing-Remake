#pragma once
#include <vector>
#include "BadGuy.h"
#include "BadBulletManager.h"

// ==========================================
// ENEMY SPAWNER creates and manages all enemies
// ==========================================
class BadGuySpawner
{
private:
    std::vector<BadGuy> badGuys;    // all enemies currently alive

    int spawnCooldown;        // counts frames until next spawn
    int enemySpawnDelay;             // 400 frames = spawn new enemy

    bool canSpawnBadGuys;   // false during boss fight

public:
    BadGuySpawner();   // sets spawnDelay=400, canSpawn=true

    void UpdateAllBadGuys(SDL_Renderer* renderer, BadBulletManager& enemyBullets); // spawn, move, shoot, remove dead
    void DrawAllBadGuys(SDL_Renderer* renderer);
    std::vector<BadGuy>& GetAllBadGuys();   // used by HitChecker

    void StopSpawningBadGuys();       // called when boss spawns
    void StartSpawningBadGuys();      // re-enable (not used yet, but here for completeness)
    void RemoveAllBadGuys();      // clears vector (restart or boss)
};
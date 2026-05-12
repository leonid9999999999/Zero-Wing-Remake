#pragma once

#include <vector>
#include "SpaceRock.h"


// ===================
// asteroid manager
// ====================

class RockController
{
private:
    std::vector<SpaceRock> rocks; // all rocks on screen

    int timeToNextRock; // frames until next rock spawns
    int rockSpawnDelay;   // 140 frames during wave 1
    bool canSpawn;  // false after wave 2 starts

public:
    RockController();

    void UpdateAll(SDL_Renderer* renderer);   // spawn, move, remove dead rocks
    void DrawAll(SDL_Renderer* renderer);
    std::vector<SpaceRock>& GetAllRocks();  // used by HitChecker

    void StopRockSpawn();
    void StartRockSpawn();
    void RemoveAllRocks();   // clear vector (wave 2 or restart)
    void ChangeSpawnDelay(int newDelay);
};
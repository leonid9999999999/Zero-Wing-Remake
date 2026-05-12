#include "RockController.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

// ============
// CONSTRUCTOR
// ============
RockController::RockController()
{
    timeToNextRock = 0;
    rockSpawnDelay = 180;   // frames between rock spawns
    canSpawn = true; // rocks enabled by default (wave 1)
}

// =============================================
// UPDATE ALL ROCKS (spawn + move + remove dead)
// ==============================================
void RockController::UpdateAll(SDL_Renderer* renderer)
{
    // SPAWN NEW ROCKS
    timeToNextRock++;
    if (canSpawn && timeToNextRock >= rockSpawnDelay)
    {
        int randomHeight = rand() % 1000 + 50; // range 50-1050 (avoid edges)
        SpaceRock newRock(1600, randomHeight);  // spawn at right edge
        newRock.LoadPicture(renderer);
        rocks.push_back(newRock);
        timeToNextRock = 0;
    }

    // MOVE ALL ROCKS
    for (auto& rock : rocks)
        rock.Move();


    // REMOVE DEAD ROCKS (off screen or destroyed)
    rocks.erase(
        std::remove_if(rocks.begin(), rocks.end(),
            [](SpaceRock& r) { return !r.IsAlive(); }),
        rocks.end()

    );

}


// ==============
// DRAW ALL ROCKS
// ===============
void RockController::DrawAll(SDL_Renderer* renderer)
{
    for (auto& rock : rocks)
        rock.Draw(renderer);
}


std::vector<SpaceRock>& RockController::GetAllRocks() { return rocks; }



void RockController::StopRockSpawn() { canSpawn = false; }
void RockController::StartRockSpawn() { canSpawn = true; }
void RockController::RemoveAllRocks() { rocks.clear(); }
void RockController::ChangeSpawnDelay(int newDelay) { rockSpawnDelay = newDelay; }
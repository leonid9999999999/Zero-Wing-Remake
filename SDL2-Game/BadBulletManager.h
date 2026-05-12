#pragma once
#include <vector>
#include "BadBullet.h"

// ============================================
// BAD BULLET MANAGER handles all enemy bullets
// ============================================
class BadBulletManager
{
private:
    std::vector<BadBullet> badBullets;  // every bullet currently on screen

public:
    void AddNewBadBullet(int startX, int startY, SDL_Renderer* renderer);  // enemy calls this when shooting
    void UpdateAllBadBullets();    // moves every bullet, removes dead ones
    void DrawAllBadBullets(SDL_Renderer* renderer);
    std::vector<BadBullet>& GetAllBadBullets();  // used by HitChecker for collisions
    void RemoveAllBadBullets();     // clears all bullets (restart or boss spawn)
};
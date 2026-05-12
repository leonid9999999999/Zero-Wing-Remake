#pragma once

#include <vector>
#include "MyBullet.h"

// ========================
// PLAYER BULLET MANAGER
// ======================

class MyBulletManager
{

private:

    std::vector<MyBullet> myBullets; //all bullets on screen

public:
    void AddNewBullet(int startX, int startY, SDL_Renderer* renderer);
    void UpdateAllBullets();   // move bullets, remove dead ones
    void DrawAllBullets(SDL_Renderer* renderer);

    std::vector<MyBullet>& GetAllBullets();   // used by HitChecker
    void RemoveAllBullets(); // clear vector (restart or boss)

};
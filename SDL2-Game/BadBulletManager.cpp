#include "BadBulletManager.h"
#include <algorithm>

// ==============
// ADD NEW BULLET
// ===============
void BadBulletManager::AddNewBadBullet(int startX, int startY, SDL_Renderer* renderer)
{
    BadBullet newBullet(startX, startY);
    newBullet.LoadPicture(renderer);
    badBullets.push_back(newBullet);
}

// ====================
// UPDATE ALL BULLETS
// ==================
void BadBulletManager::UpdateAllBadBullets()
{
    // move every bullet
    for (auto& bullet : badBullets)
        bullet.Fly();

    // remove dead ones (off screen or hit player)
    badBullets.erase(
        std::remove_if(badBullets.begin(), badBullets.end(),
            [](BadBullet& b) { return !b.IsAlive(); }),
        badBullets.end()
    );
}

// ===============
// DRAW ALL BULLETS
// ================
void BadBulletManager::DrawAllBadBullets(SDL_Renderer* renderer)
{
    for (auto& bullet : badBullets)
        bullet.Draw(renderer);

}

std::vector<BadBullet>& BadBulletManager::GetAllBadBullets() { return badBullets; }
void BadBulletManager::RemoveAllBadBullets() { badBullets.clear(); }
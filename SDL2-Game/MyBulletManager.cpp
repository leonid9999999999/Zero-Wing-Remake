#include "MyBulletManager.h"
#include <algorithm>

// =================================================
// ADD NEW BULLET (called when player presses space)
// ==================================================

void MyBulletManager::AddNewBullet(int startX, int startY, SDL_Renderer* renderer)
{
    MyBullet newBullet(startX, startY);
    newBullet.LoadBulletPicture(renderer);
    myBullets.push_back(newBullet);

}

// =============================================
// UPDATE ALL BULLETS (move + remove dead ones)
// =============================================
void MyBulletManager::UpdateAllBullets()
{
    // move every bullet
    for (auto& bullet : myBullets)
        bullet.Fly();




    // remove bullets that are dead (off screen or hit something)
    myBullets.erase(
        std::remove_if(myBullets.begin(), myBullets.end(),
            [](MyBullet& b) { return !b.IsAlive(); }),
        myBullets.end()

    );
}

// =================
// DRAW ALL BULLETS
// =================
void MyBulletManager::DrawAllBullets(SDL_Renderer* renderer)
{
    for (auto& bullet : myBullets)
        bullet.Draw(renderer);

}

std::vector<MyBullet>& MyBulletManager::GetAllBullets() { return myBullets; }

void MyBulletManager::RemoveAllBullets() { myBullets.clear(); }
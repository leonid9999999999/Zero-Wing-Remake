#include "SpaceRock.h"
#include "LoadStuff.h"
#include <cstdlib>

// ============
// CONSTRUCTOR
// ===========
SpaceRock::SpaceRock(int startX, int startY)
{
    rockTexture = nullptr;

    rockRect.x = startX;
    rockRect.y = startY;
    rockRect.w = 80;
    rockRect.h = 80;

    flySpeedX = 4;// moves left at 4px/frame

    // random vertical movement (0, +2, or -2) so rocks aren't boring
    int randomMove = rand() % 3;
    if (randomMove == 0) flySpeedY = 0;
    else if (randomMove == 1) flySpeedY = 2;
    else flySpeedY = -2;

    isAlive = true;

}

// =============
// LOAD TEXTURE
// =============
bool SpaceRock::LoadPicture(SDL_Renderer* renderer)
{
    rockTexture = LoadStuff::LoadPicture("assets/textures/asteroid.bmp", renderer);
    return rockTexture != nullptr;

}

// ==============
// MOVE ASTEROID
// =============
void SpaceRock::Move()
{
    rockRect.x -= flySpeedX;
    rockRect.y += flySpeedY;

    // off screen left -> kill it
    if (rockRect.x < -100) isAlive = false;

    // boundaries (clamp to screen edges)
    if (rockRect.y < 0) rockRect.y = 0;

    if (rockRect.y > 1120) rockRect.y = 1120;  // 1200 - 80 = 1120
}

// ==============
// DRAW ASTEROID
// =============
void SpaceRock::Draw(SDL_Renderer* renderer)
{
    if (isAlive && rockTexture)
        SDL_RenderCopy(renderer, rockTexture, nullptr, &rockRect);

}


SDL_Rect SpaceRock::GetPosition() { return rockRect; }
bool SpaceRock::IsAlive() { return isAlive; }
void SpaceRock::Kill() { isAlive = false; }
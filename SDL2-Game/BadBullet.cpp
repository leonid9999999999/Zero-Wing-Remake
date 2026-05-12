#include "BadBullet.h"
#include "LoadStuff.h"

// ===========
// CONSTRUCTOR
// ============
BadBullet::BadBullet(int startX, int startY)
{
    bulletPic = nullptr;

    bulletPos.x = startX;
    bulletPos.y = startY;
    bulletPos.w = 35;  // width (slightly smaller than player bullet)
    bulletPos.h = 20; // height

    flySpeed = 6; // moves left, slower than player bullet (8)
    isAlive = true;

}


// ===========
// LOAD TEXTURE
// =============
bool BadBullet::LoadPicture(SDL_Renderer* renderer)
{
    bulletPic = LoadStuff::LoadPicture("assets/textures/enemy_projectile.bmp", renderer);
    return bulletPic != nullptr;

}

// ============
// FLY (move left)
// ==============
void BadBullet::Fly()
{

    bulletPos.x -= flySpeed;
    if (bulletPos.x < -bulletPos.w) isAlive = false;   // off screen, kill it
}

// ====
// DRAW
// ===
void BadBullet::Draw(SDL_Renderer* renderer)

{
    if (bulletPic) SDL_RenderCopy(renderer, bulletPic, nullptr, &bulletPos);

}

bool BadBullet::IsAlive() { return isAlive; }
void BadBullet::Destroy() { isAlive = false; }
SDL_Rect BadBullet::GetPosition() { return bulletPos; }
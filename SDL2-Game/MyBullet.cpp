#include "MyBullet.h"
#include "LoadStuff.h"

// =============
// CONSTRUCTOR
// =============
MyBullet::MyBullet(int startX, int startY)

{
    bulletPic = nullptr;

    bulletPos.x = startX;
    bulletPos.y = startY;
    bulletPos.w = 40;
    bulletPos.h = 20;

    flySpeed = 8;   // flies right, faster than enemy bullets (6)
    isAlive = true;
}

// ==============
// LOAD TEXTURE
// ============
bool MyBullet::LoadBulletPicture(SDL_Renderer* renderer)
{
    bulletPic = LoadStuff::LoadPicture("assets/textures/projectile.bmp", renderer);
    return bulletPic != nullptr;

}

// ====
// FLY (move right)
// ====
void MyBullet::Fly()
{
    bulletPos.x += flySpeed;
    if (bulletPos.x > 1600) isAlive = false;  // off screen right, kill it
}

// =======
// DRAW
// ======
void MyBullet::Draw(SDL_Renderer* renderer)
{
    if (bulletPic) SDL_RenderCopy(renderer, bulletPic, nullptr, &bulletPos);

}

bool MyBullet::IsAlive() { return isAlive; }
void MyBullet::Destroy() { isAlive = false; }
SDL_Rect MyBullet::GetBulletPosition() { return bulletPos; }
#include "MyHero.h"
#include "LoadStuff.h"
#include <iostream>




MyHero::MyHero()
{
    heroPic = nullptr;

    heroPos.x = 200;
    heroPos.y = 500;
    heroPos.w = 100;
    heroPos.h = 80;

    flySpeed = 5; // pixels per frame, feels responsive
    healthPoints = 3;  // three hits before game over

}

// =======================
// LOAD PLAYER SHIP TEXTURE
// =====================
bool MyHero::LoadHeroPicture(SDL_Renderer* renderer)
{
    heroPic = LoadStuff::LoadPicture("assets/textures/player_ship.bmp", renderer);
    if (!heroPic) std::cout << "ERROR: player ship texture failed to load!" << std::endl;
    return heroPic != nullptr;

}

// ====================================
// KEYBOARD CONTROL (WASD + arrow keys)
// ===================================
void MyHero::GetKeyboardInput(const Uint8* keys)
{
    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) heroPos.y -= flySpeed;
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) heroPos.y += flySpeed;
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) heroPos.x -= flySpeed;
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) heroPos.x += flySpeed;

}

// =======================================
// BOUNDARY LIMITS (keep player on screen)
// =======================================
void MyHero::Move()
{
    // left edge
    if (heroPos.x < 0) heroPos.x = 0;

    // right edge (1600 - ship width = 1500)
    if (heroPos.x + heroPos.w > 1600) heroPos.x = 1600 - heroPos.w;

    // top edge
    if (heroPos.y < 0) heroPos.y = 0;


    // bottom edge (1200 - ship height = 1120)
    if (heroPos.y + heroPos.h > 1200) heroPos.y = 1200 - heroPos.h;
}

// ==========
// DRAW SHIP
// ==========
void MyHero::Draw(SDL_Renderer* renderer)
{
    if (heroPic) SDL_RenderCopy(renderer, heroPic, nullptr, &heroPos);
}

// ===========
// CLEANUP
// =========
void MyHero::DeleteTexture()
{
    if (heroPic) SDL_DestroyTexture(heroPic);
}

SDL_Rect MyHero::GetHeroPosition() { return heroPos; }


void MyHero::GetDamage()
{
    healthPoints--;
    std::cout << "HIT! HP left: " << healthPoints << std::endl;
    if (healthPoints < 0) healthPoints = 0;

}


int MyHero::GetHealthLeft() { return healthPoints; }
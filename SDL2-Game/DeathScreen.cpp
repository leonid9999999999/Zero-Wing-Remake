#include "DeathScreen.h"
#include "LoadStuff.h"
#include <iostream>

// ============
// CONSTRUCTOR
// ===========
DeathScreen::DeathScreen()
{
    backgroundPic = nullptr;
    restartPic = nullptr;
    menuPic = nullptr;



    // button positions (screen is 1600x1200, buttons centered)
    restartButtonZone = { 550, 500, 500, 150 };
    menuButtonZone = { 550, 700, 500, 150 };

}

// =================
// LOAD ALL TEXTURES
// =================
bool DeathScreen::LoadAllPictures(SDL_Renderer* renderer)
{
    backgroundPic = LoadStuff::LoadPicture("assets/textures/gameover_background.bmp", renderer);
    restartPic = LoadStuff::LoadPicture("assets/textures/restart_button.bmp", renderer);
    menuPic = LoadStuff::LoadPicture("assets/textures/menu_button.bmp", renderer);

    if (!backgroundPic) std::cout << "Failed to load game over background!" << std::endl;
    if (!restartPic) std::cout << "Failed to load restart button!" << std::endl;
    if (!menuPic) std::cout << "Failed to load menu button!" << std::endl;

    return true;
}

// =====================
// HANDLE MOUSE INPUT
// ===================
void DeathScreen::HandleInput(SDL_Event& event, bool& needRestart, bool& backToMenu)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        // check restart button click
        if (mouseX >= restartButtonZone.x && mouseX <= restartButtonZone.x + restartButtonZone.w &&
            mouseY >= restartButtonZone.y && mouseY <= restartButtonZone.y + restartButtonZone.h)
        {
            needRestart = true;
            std::cout << "RESTART GAME!" << std::endl;

        }

        // check menu button click
        if (mouseX >= menuButtonZone.x && mouseX <= menuButtonZone.x + menuButtonZone.w &&
            mouseY >= menuButtonZone.y && mouseY <= menuButtonZone.y + menuButtonZone.h)
        {
            backToMenu = true;
            std::cout << "RETURN TO MENU!" << std::endl;

        }

    }
}

// ================
// DRAW EVERYTHING
// ===============
void DeathScreen::Draw(SDL_Renderer* renderer)
{
    if (backgroundPic) SDL_RenderCopy(renderer, backgroundPic, nullptr, nullptr);
    if (restartPic) SDL_RenderCopy(renderer, restartPic, nullptr, &restartButtonZone);
    if (menuPic) SDL_RenderCopy(renderer, menuPic, nullptr, &menuButtonZone);

}

// ==================
// CLEANUP TEXTURES
// =====================
void DeathScreen::DeleteTextures()
{
    if (backgroundPic) SDL_DestroyTexture(backgroundPic);
    if (restartPic) SDL_DestroyTexture(restartPic);
    if (menuPic) SDL_DestroyTexture(menuPic);


}
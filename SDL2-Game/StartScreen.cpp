#include "StartScreen.h"
#include "LoadStuff.h"
#include <iostream>

// =============================
// CONSTRUCTOR - BUTTON POSITIONS
// ==============================
StartScreen::StartScreen()
{
    backgroundPic = nullptr;
    gameLogoPic = nullptr;
    startButtonPic = nullptr;
    exitButtonPic = nullptr;

    // buttons centered on 1600x1200 screen
    startButtonZone = { 550, 500, 500, 140 };
    exitButtonZone = { 550, 700, 500, 140 };
}

// ==================
// LOAD ALL TEXTURES
// ==================
bool StartScreen::LoadAllPictures(SDL_Renderer* renderer)
{


    backgroundPic = LoadStuff::LoadPicture("assets/textures/menu_background.bmp", renderer);
    if (!backgroundPic) std::cout << "Failed to load background!" << std::endl;



    gameLogoPic = LoadStuff::LoadPicture("assets/textures/logo.bmp", renderer);
    if (!gameLogoPic) std::cout << "Failed to load logo!" << std::endl;


    startButtonPic = LoadStuff::LoadPicture("assets/textures/button_start.bmp", renderer);
    if (!startButtonPic) std::cout << "Failed to load START button!" << std::endl;


    exitButtonPic = LoadStuff::LoadPicture("assets/textures/button_exit.bmp", renderer);
    if (!exitButtonPic) std::cout << "Failed to load EXIT button!" << std::endl;

    return true;


}

// ===================
// HANDLE MOUSE INPUT
// ==================
void StartScreen::HandleMenuInput(SDL_Event& event, bool& wantToPlay, bool& wantToExit)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        // check START button click
        if (mouseX >= startButtonZone.x && mouseX <= startButtonZone.x + startButtonZone.w &&
            mouseY >= startButtonZone.y && mouseY <= startButtonZone.y + startButtonZone.h)
        {
            wantToPlay = true;
            std::cout << "START BUTTON PRESSED!" << std::endl;

        }

        // check EXIT button click
        if (mouseX >= exitButtonZone.x && mouseX <= exitButtonZone.x + exitButtonZone.w &&
            mouseY >= exitButtonZone.y && mouseY <= exitButtonZone.y + exitButtonZone.h)
        {
            wantToExit = true;
            std::cout << "EXIT BUTTON PRESSED!" << std::endl;

        }
    }

}

// ================
// DRAW EVERYTHING
// ================
void StartScreen::Draw(SDL_Renderer* renderer)
{
    if (backgroundPic) SDL_RenderCopy(renderer, backgroundPic, nullptr, nullptr);

    SDL_Rect logoPos = { 350, 120, 900, 250 };
    if (gameLogoPic) SDL_RenderCopy(renderer, gameLogoPic, nullptr, &logoPos);

    if (startButtonPic) SDL_RenderCopy(renderer, startButtonPic, nullptr, &startButtonZone);
    if (exitButtonPic) SDL_RenderCopy(renderer, exitButtonPic, nullptr, &exitButtonZone);
}

// ================
// CLEANUP TEXTURES
// =================
void StartScreen::DeleteTextures()
{

    if (backgroundPic) SDL_DestroyTexture(backgroundPic);

    if (gameLogoPic) SDL_DestroyTexture(gameLogoPic);

    if (startButtonPic) SDL_DestroyTexture(startButtonPic);

    if (exitButtonPic) SDL_DestroyTexture(exitButtonPic);

}
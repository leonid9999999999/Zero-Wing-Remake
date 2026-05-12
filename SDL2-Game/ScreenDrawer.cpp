#include "ScreenDrawer.h"

// ===========================================
// DRAW HEALTH BAR (red squares, 50x50 each)
// ==========================================

void ScreenDrawer::DrawHealthBar(SDL_Renderer* graphics, int hpLeft)
{
    // clamp health to valid range (0-5)
    if (hpLeft > 5) hpLeft = 5;
    if (hpLeft < 0) hpLeft = 0;


    for (int i = 0; i < hpLeft; i++)

    {
        // position: start at x=30, space 70px between squares
        SDL_Rect heartRect = { 30 + (i * 70), 30, 50, 50 };
        SDL_SetRenderDrawColor(graphics, 255, 0, 0, 255); // bright red
        SDL_RenderFillRect(graphics, &heartRect);

    }
}


// ====================================
// DRAW SCORE BAR (green progress bar)
// ====================================
void ScreenDrawer::DrawPlayerScore(SDL_Renderer* graphics, int points)
{
    // width = points/5, max 300 (1500 points = full bar)
    int barWidth = points / 5;
    if (barWidth > 300) barWidth = 300;

    SDL_Rect scoreRect = { 30, 100, barWidth, 30 };
    SDL_SetRenderDrawColor(graphics, 0, 255, 0, 255); // green
    SDL_RenderFillRect(graphics, &scoreRect);



}
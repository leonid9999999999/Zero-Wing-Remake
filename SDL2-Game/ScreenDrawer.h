#pragma once

#include <SDL.h>

// ========================
// health and score bars
// ========================

class ScreenDrawer
{
public:
    void DrawHealthBar(SDL_Renderer* graphics, int hpLeft); // red squares top left
    void DrawPlayerScore(SDL_Renderer* graphics, int points); // green progress bar
};
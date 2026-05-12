#pragma once

#include <SDL.h>
#include <iostream>

#include "StartScreen.h"
#include "DeathScreen.h"
#include "MyHero.h"
#include "MyBulletManager.h"
#include "BadGuySpawner.h"
#include "BadBulletManager.h"
#include "HitChecker.h"
#include "PointCounter.h"
#include "ScreenDrawer.h"
#include "BigBadGuy.h"
#include "RockController.h"
#include "WaveChanger.h"

// ===========
// GAME STATES
// ==============
enum class GameMode
{
    MENU, // main menu
    FIGHT,  // playing the game
    GAMEOVER, // player died
    EXIT   // closing
};

// ============================
// everything falls apart here
// =============================
class Game
{
private:
    SDL_Window* mainWindow;
    SDL_Renderer* graphics;
    bool gameWorking;

    GameMode currentMode;

    StartScreen startMenu;
    DeathScreen deathScreen;
    MyHero hero;
    MyBulletManager myBullets;
    BadGuySpawner badGuys;
    BadBulletManager badBullets;
    RockController spaceRocks;
    PointCounter gamePoints;
    ScreenDrawer ui;
    BigBadGuy finalBoss;
    WaveChanger waveSystem;

    bool isBossHere;  // prevents spawning multiple bosses
    bool wave2Started;  // my dirty fix for wave transitions

    void RestartGame();
    void SpawnTheBoss();
    void CheckAllCollisions();

public:
    Game();
    ~Game();

    bool SetupGame();
    void MainLoop();

    void GetInput();
    void UpdateGame();
    void DrawGame();

    void Cleanup();
    bool IsGameRunning();
};
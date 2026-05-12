#include "Game.h"
#include <iostream>

// =============
// CONSTRUCTOR
// ===========
Game::Game()
{
    mainWindow = nullptr;
    graphics = nullptr;
    gameWorking = false;
    isBossHere = false;
    wave2Started = false;  // my dirty flag for wave transitions
}

// ============
// DESTRUCTOR
// ===========
Game::~Game()
{
    Cleanup();

}

// ==========================================
// SETUP GAME (window, renderer, textures)
// ==========================================
bool Game::SetupGame()

{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "ERROR: SDL failed to initialise!" << std::endl;
        return false;
    }

    mainWindow = SDL_CreateWindow(
        "Zero Wing Remake",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1600, 1200, 0
    );

    if (!mainWindow)
    {
        std::cout << "ERROR: window creation failed!" << std::endl;
        return false;

    }

    graphics = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!graphics)
    {
        std::cout << "ERROR: renderer creation failed!" << std::endl;
        return false;


    }
    


    currentMode = GameMode::MENU;

    // load all the assets
    startMenu.LoadAllPictures(graphics);
    deathScreen.LoadAllPictures(graphics);
    hero.LoadHeroPicture(graphics);
    finalBoss.LoadPicture(graphics);

    gameWorking = true;
    std::cout << "GAME STARTED!" << std::endl;

    return true;
}

// ================
// MAIN GAME LOOP
// ================

void Game::MainLoop()
{
    while (gameWorking)
    {
        GetInput();
        UpdateGame();
        DrawGame();
        SDL_Delay(16); // roughly 60 FPS
    }
}

// ========================
// RESTART GAME AFTER DEATH
// =========================
void Game::RestartGame()
{
    std::cout << "RESTARTING GAME!" << std::endl;

    // recreate everything (easier than resetting each system)
    hero = MyHero();
    hero.LoadHeroPicture(graphics);

    myBullets = MyBulletManager();
    badGuys = BadGuySpawner();
    badBullets = BadBulletManager();
    spaceRocks = RockController();
    gamePoints = PointCounter();
    waveSystem = WaveChanger();

    finalBoss = BigBadGuy();
    finalBoss.LoadPicture(graphics);

    isBossHere = false;
    wave2Started = false;
    currentMode = GameMode::FIGHT;


}

// =========================================
// SPAWN THE BOSS (called from wave system)           ;) good Luck
// ==========================================
void Game::SpawnTheBoss()
{
    std::cout << "BOSS SPAWNED! FIGHT!" << std::endl;
    finalBoss.StartFight();
    isBossHere = true;

    // clear all enemies and rocks, stop spawning
    badGuys.StopSpawningBadGuys();
    badGuys.RemoveAllBadGuys();
    spaceRocks.StopRockSpawn();
    spaceRocks.RemoveAllRocks();
    badBullets.RemoveAllBadBullets();
}

// ==============================================
// CHECK ALL COLLISIONS (wrapped in one function)
// ===============================================
void Game::CheckAllCollisions()
{
    HitChecker::CheckMyBulletsVsEnemies(myBullets, badGuys, gamePoints);
    HitChecker::CheckEnemyBulletsVsPlayer(badBullets, hero);
    HitChecker::CheckEverythingVsRocks(myBullets, spaceRocks, hero, gamePoints);
    HitChecker::CheckMyBulletsVsBoss(myBullets, finalBoss, gamePoints);
}

// ================================
// HANDLE INPUT (keyboard + mouse)
// ==============================
void Game::GetInput()
{
    SDL_Event event;
    bool wantToPlay = false;
    bool wantToExit = false;
    bool needRestart = false;
    bool backToMenu = false;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gameWorking = false;

        }



        if (currentMode == GameMode::MENU)
        {
            startMenu.HandleMenuInput(event, wantToPlay, wantToExit);
        }


        if (currentMode == GameMode::GAMEOVER)
        {
            deathScreen.HandleInput(event, needRestart, backToMenu);

        }

        if (event.type == SDL_KEYDOWN && currentMode == GameMode::FIGHT)
        {
            if (event.key.keysym.sym == SDLK_SPACE)
            {
                SDL_Rect heroPos = hero.GetHeroPosition();
                myBullets.AddNewBullet(heroPos.x + 80, heroPos.y + 30, graphics);  // bullet from ship nose

            }
        }
    }

    // continuous keyboard input for movement (not event-based)
    if (currentMode == GameMode::FIGHT)

    {
        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        hero.GetKeyboardInput(keys);

    }

    // handle menu flags
    if (wantToPlay) currentMode = GameMode::FIGHT;
    if (wantToExit) gameWorking = false;
    if (needRestart) RestartGame();
    if (backToMenu) currentMode = GameMode::MENU;
}

// =========================================================
// UPDATE GAME LOGIC (movement, spawning, waves, collisions)
// ==========================================================
void Game::UpdateGame()
{
    switch (currentMode)
    {
    case GameMode::MENU:
        break;

    case GameMode::FIGHT:
    {
        hero.Move();
        myBullets.UpdateAllBullets();
        badBullets.UpdateAllBadBullets();

        // wave management based on score
        waveSystem.CheckAndUpdateWave(gamePoints.GetCurrentPoints());
        WaveType currentWave = waveSystem.GetCurrentWave();

        // WAVE 1: ASTEROIDS ONLY
        if (currentWave == WaveType::ASTEROIDS)
        {
            if (!wave2Started)
            {
                spaceRocks.StartRockSpawn();
                spaceRocks.ChangeSpawnDelay(140);
                wave2Started = true;
            }
            spaceRocks.UpdateAll(graphics);
        }


        // WAVE 2: ENEMIES ONLY
        if (currentWave == WaveType::ENEMIES)
        {
            spaceRocks.StopRockSpawn();
            spaceRocks.RemoveAllRocks();

            badGuys.UpdateAllBadGuys(graphics, badBullets);


        }



        // WAVE 3: BOSS
        if (currentWave == WaveType::FINAL_BOSS && !isBossHere)
        {
            SpawnTheBoss();

        }

        // update rocks if not in wave 2 (wave 2 has no rocks)
        if (currentWave != WaveType::ENEMIES)
        {
            spaceRocks.UpdateAll(graphics);

        }



        // boss update and shooting
        finalBoss.Update();

        if (finalBoss.IsAlive() && finalBoss.CanFire())
        {
            SDL_Rect bossPos = finalBoss.GetPosition();
            badBullets.AddNewBadBullet(bossPos.x, bossPos.y + 100, graphics); // bullet from boss centre
            finalBoss.ResetFireTimer();
        }

        CheckAllCollisions();

        // player death
        if (hero.GetHealthLeft() <= 0)
        {
            std::cout << "GAME OVER!" << std::endl;
            currentMode = GameMode::GAMEOVER;
        }
        break;
    }

    case GameMode::GAMEOVER:
        break;

    case GameMode::EXIT:
        gameWorking = false;
        break;
    }
}

// ================
// DRAW EVERYTHING
// ===============
void Game::DrawGame()
{
    SDL_SetRenderDrawColor(graphics, 0, 0, 0, 255);
    SDL_RenderClear(graphics);

    switch (currentMode)
    {
    case GameMode::MENU:
        startMenu.Draw(graphics);
        break;


    case GameMode::FIGHT:
        hero.Draw(graphics);
        myBullets.DrawAllBullets(graphics);
        badBullets.DrawAllBadBullets(graphics);
        spaceRocks.DrawAll(graphics);
        badGuys.DrawAllBadGuys(graphics);
        finalBoss.Draw(graphics);
        ui.DrawHealthBar(graphics, hero.GetHealthLeft());
        ui.DrawPlayerScore(graphics, gamePoints.GetCurrentPoints());
        break;

    case GameMode::GAMEOVER:
        deathScreen.Draw(graphics);
        break;

    case GameMode::EXIT:
        break;

    }

    SDL_RenderPresent(graphics);
}

// ===================================================
// CLEANUP (free textures, destroy window, quit SDL)
// ==================================================
void Game::Cleanup()
{
    startMenu.DeleteTextures();
    deathScreen.DeleteTextures();
    hero.DeleteTexture();
    SDL_DestroyRenderer(graphics);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

bool Game::IsGameRunning()
{

    return gameWorking;
}
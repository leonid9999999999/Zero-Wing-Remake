#include "WaveChanger.h"
#include <iostream>


// ===================================
// CONSTRUCTOR START WITH ASTEROIDS
// ===================================
WaveChanger::WaveChanger()
{
    currentWave = WaveType::ASTEROIDS;
    std::cout << "WAVE 1: ASTEROIDS" << std::endl;

}

// ============================
// CHECK SCORE AND UPDATE WAVE
// ===========================
void WaveChanger::CheckAndUpdateWave(int playerScore)
{
    WaveType newWave = currentWave;

    // wave thresholds
    // 0-499 points   = asteroids
    // 500-1499 points = enemies
    // 1500+ points   = boss
    if (playerScore < 500)
    {
        newWave = WaveType::ASTEROIDS;

    }

    else if (playerScore < 1500)
    {
        newWave = WaveType::ENEMIES;
    }

    else
    {
        newWave = WaveType::FINAL_BOSS;
    }

    // print message when wave changes
    if (newWave != currentWave)
    {
        currentWave = newWave;

        if (currentWave == WaveType::ENEMIES)
            std::cout << "WAVE 2: ENEMIES!" << std::endl;
        else if (currentWave == WaveType::FINAL_BOSS)
            std::cout << "WAVE 3: BOSS!!!" << std::endl;
    }
}

// =================
// GET CURRENT WAVE
// =================
WaveType WaveChanger::GetCurrentWave()
{
    return currentWave;

}

// +====================================================
// FORCE WAVE CHANGE (not used, but here for debugging)
// ====================================================
void WaveChanger::ForceWave(WaveType newWave)
{

    currentWave = newWave;
}
#pragma once

// ==========
// WAVE TYPES
// ============
enum class WaveType
{
    ASTEROIDS, // wave 1
    ENEMIES,  // wave 2
    FINAL_BOSS // wave 3 (boss fight)
};

// =============================================
// WAVE MANAGER (changes waves based on score)
// ===========================================

class WaveChanger
{
private:
    WaveType currentWave;  // starts at ASTEROIDS

public:
    WaveChanger();

    void CheckAndUpdateWave(int playerScore);     // thresholds: 500 and 1500
    WaveType GetCurrentWave();
    void ForceWave(WaveType newWave);  // not used yet, but here if needed
};
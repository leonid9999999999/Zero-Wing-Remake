#include "PointCounter.h"
#include <iostream>

// =============================
// CONSTRUCTOR START FROM ZERO
// ============================
PointCounter::PointCounter()
{
    currentPoints = 0;

    std::cout << "Score counter initialised!" << std::endl;

}

// ===========================================
// ADD POINTS (100 enemy, 50 rock, 200 boss)
// ==========================================
void PointCounter::AddPoints(int howMany)
{
    if (howMany > 0)    // ignore negative values just in case
    {
        currentPoints += howMany;
        std::cout << "+" << howMany << " points! Total: " << currentPoints << std::endl;

    }
}

// ================
// GET CURRENT SCORE
// =================
int PointCounter::GetCurrentPoints()
{
    return currentPoints;
}

// ===============================
// RESET SCORE (called on restart)
// ===============================
void PointCounter::ResetPoints()
{
    currentPoints = 0;
    std::cout << "Score reset to zero!" << std::endl;

}
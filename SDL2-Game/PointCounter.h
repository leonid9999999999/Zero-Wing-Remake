#pragma once

// ============
// SCORE COUNTER
// =========

class PointCounter
{
private:
    int currentPoints;// goes up when killing stuff

public:
    PointCounter();

    void AddPoints(int howMany); // 100 for enemy, 50 for rock, 200 for boss hit
    int GetCurrentPoints();
    void ResetPoints(); // called on restart
};
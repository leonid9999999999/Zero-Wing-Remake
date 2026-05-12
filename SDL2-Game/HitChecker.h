#pragma once

#include "MyBulletManager.h"
#include "BadGuySpawner.h"
#include "BadBulletManager.h"
#include "BigBadGuy.h"
#include "PointCounter.h"
#include "MyHero.h"
#include "RockController.h"

// ===========================
// static class, no objects
// =========================
class HitChecker
{

public:
    // my bullets vs enemies (death +100 points)
    static void CheckMyBulletsVsEnemies(
        MyBulletManager& myBullets,
        BadGuySpawner& badGuys,
        PointCounter& points

    );


    // enemy bullets vs player (damage)
    static void CheckEnemyBulletsVsPlayer(
        BadBulletManager& enemyBullets,
        MyHero& hero
    );


    // my bullets vs boss ( -1 hp, +200 points)
    static void CheckMyBulletsVsBoss(
        MyBulletManager& myBullets,
        BigBadGuy& boss,
        PointCounter& points
    );

    // everything vs rocks (bullets kill rocks, rocks kill player)
    static void CheckEverythingVsRocks(
        MyBulletManager& myBullets,
        RockController& rocks,
        MyHero& hero,
        PointCounter& points

    );

};
#include "HitChecker.h"
#include <iostream>

// =========================
// MY BULETS VS ENEMIES
// =====================
void HitChecker::CheckMyBulletsVsEnemies(
    MyBulletManager& myBullets,
    BadGuySpawner& badGuys,
    PointCounter& points)
{
    auto& bullets = myBullets.GetAllBullets();
    auto& enemies = badGuys.GetAllBadGuys();

    for (auto& bullet : bullets)
    {
        SDL_Rect bulletPos = bullet.GetBulletPosition();

        for (auto& enemy : enemies)
        {
            SDL_Rect enemyPos = enemy.GetPosition();

            if (SDL_HasIntersection(&bulletPos, &enemyPos))
            {
                bullet.Destroy();
                enemy.Kill();
                points.AddPoints(100); // 100 points per enemy kill
            }
        }
    }
}

// ========================
// ENEMY BULLETS VS PLAYER
// ========================
void HitChecker::CheckEnemyBulletsVsPlayer(
    BadBulletManager& enemyBullets,
    MyHero& hero)
{
    auto& bullets = enemyBullets.GetAllBadBullets();
    SDL_Rect heroPos = hero.GetHeroPosition();

    for (auto& bullet : bullets)
    {
        SDL_Rect bulletPos = bullet.GetPosition();

        if (SDL_HasIntersection(&bulletPos, &heroPos))
        {
            bullet.Destroy();
            hero.GetDamage();  // player loses 1 HP
        }
    }

}

// ===================
// MY BULLETS VS BOSS
// ==================
void HitChecker::CheckMyBulletsVsBoss(
    MyBulletManager& myBullets,
    BigBadGuy& boss,
    PointCounter& points)
{
    if (!boss.IsAlive()) return; // boss already dead

    auto& bullets = myBullets.GetAllBullets();
    SDL_Rect bossPos = boss.GetPosition();

    for (auto& bullet : bullets)
    {
        SDL_Rect bulletPos = bullet.GetBulletPosition();

        if (SDL_HasIntersection(&bulletPos, &bossPos))
        {
            bullet.Destroy();
            boss.GetHit();  // boss loses 1 HP
            points.AddPoints(200);  // 200 points per boss hit
        }
    }
}

// =======================================
// EVERYTHING VS ROCKS (bullets + player)
// ========================================
void HitChecker::CheckEverythingVsRocks(
    MyBulletManager& myBullets,
    RockController& rocks,
    MyHero& hero,
    PointCounter& points)
{
    auto& bullets = myBullets.GetAllBullets();
    auto& allRocks = rocks.GetAllRocks();

    // bullets destroy rocks (50 points)
    for (auto& bullet : bullets)
    {
        SDL_Rect bulletPos = bullet.GetBulletPosition();

        for (auto& rock : allRocks)
        {
            SDL_Rect rockPos = rock.GetPosition();

            if (SDL_HasIntersection(&bulletPos, &rockPos))
            {
                bullet.Destroy();
                rock.Kill();
                points.AddPoints(50); // 50 points per rock
            }
        }
    }

    // player colliding with rock = damage + rock dies
    SDL_Rect heroPos = hero.GetHeroPosition();

    for (auto& rock : allRocks)
    {
        SDL_Rect rockPos = rock.GetPosition();

        if (SDL_HasIntersection(&heroPos, &rockPos))
        {
            rock.Kill();
            hero.GetDamage();    // player loses 1 HP

        }
    }
}
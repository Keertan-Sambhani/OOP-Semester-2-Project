#include "spaceship.h"
#include "C:\raylib\raylib\src\raylib.h"
#include "bullet.h"
#include "alien.h"

Spaceship::Spaceship() { entityHealth = 5; }
void Spaceship::move()
{
    if (IsKeyDown(KEY_W) && entityPosition.y > 0)
        entityPosition.y -= 5;
    if (IsKeyDown(KEY_S) && entityPosition.y < GetScreenHeight() - entityHeight - 75)
        entityPosition.y += 5;
    if (IsKeyDown(KEY_A) && entityPosition.x > 0)
        entityPosition.x -= 5;
    if (IsKeyDown(KEY_D) && entityPosition.x < GetScreenWidth() - entityWidth)
        entityPosition.x += 5;
}

void Spaceship::shoot(Sound *shootSound)
{
    double currentTime = GetTime();

    if (IsKeyDown(KEY_SPACE) && (currentTime - lastShotTime) >= shotCooldown)
    {
        PlaySound(*shootSound);
        bulletsShot.push_back(Bullet(0.20f, this, this->entityPosition.x + 10));
        bulletsShot.push_back(Bullet(0.20f, this, this->entityPosition.x - 70));
        // ((bulletsShot.end()) - 1)->bulletPosition.x -= 80; // changes the x coordinate of the second bullet released
        lastShotTime = currentTime; // Update time of last shot
    }

    // Bullet caretaking loop->redraws bullets and check for collion and if collides then removes from array
}

void Spaceship::UpdateBulletPosition(vector<Alien> &enemy, int &enemyCount)
{
    for (auto it = bulletsShot.begin(); it != bulletsShot.end();)
    {
        it->draw();
        it->bulletPosition.y -= it->speed;
        bool erased = false;
        for (int i = 0; (i < enemyCount) && (erased == false); i++)
        {
            if (CheckCollisionRecs(enemy[i].GetEntityRectangle(), it->GetBulletRectangle()))
            {

                it = bulletsShot.erase(it); // Also erase on hit
                enemy[i].entityHealth--;
                erased = true;
                break;
            }
        }

        if (!erased)
        {
            if (it->bulletPosition.y < -it->bulletHeight)
                it = bulletsShot.erase(it);
            else
                ++it;
        }
    }
}
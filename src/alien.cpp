#include "spaceship.h"
#include "C:\raylib\raylib\src\raylib.h"
#include "bullet.h"
#include "alien.h"

Alien::Alien() { entityHealth = 2; }
int Alien::collions = 0;
void Alien::move(vector<Alien> &enemy)
{
    if ((entityPosition.x >= GetScreenWidth() - entityWidth - 40) && (moveRight == true))
    {
        moveRight = false;
        moveLeft = true;

        for (auto &e : enemy)
        {
            e.entityPosition.y += 30;
        }
    }
    else if ((entityPosition.x <= 40) && (moveLeft == true))
    {
        moveLeft = false;
        moveRight = true;

        for (auto &e : enemy)
        {
            e.entityPosition.y += 30;
        }
    }

    if (moveRight == true)
        entityPosition.x += 2.5;
    else
        entityPosition.x -= 2.5;
}

bool Alien::moveRight = true;
bool Alien::moveLeft = false;

void Alien::shoot(Sound *shootSound)
{

    bulletsShot.push_back(Bullet(0.20f, this, this->entityPosition.x - (this->entityWidth) / 2));
}
void Alien::UpdateBulletPosition(Entity &player, Sound *DamageTaken)
{
    int screenHeight = GetScreenHeight();

    // Bullet caretaking loop->redraws bullets and check for collion and if collides then removes from array
    for (auto it = bulletsShot.begin(); it != bulletsShot.end();)
    {
        it->draw();
        it->bulletPosition.y += it->speed;

        if (CheckCollisionRecs(player.GetEntityRectangle(), it->GetBulletRectangle()))
        {
            PlaySound(*DamageTaken);
            it = bulletsShot.erase(it); // Also erase on hit
            player.entityHealth--;
            continue; // Skip ++it to avoid invalid iterator
        }
        if (it->bulletPosition.y >= screenHeight)
            it = bulletsShot.erase(it);

        else
            ++it;
    }
}
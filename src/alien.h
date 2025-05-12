#ifndef ALIEN
#define ALIEN
#include "bullet.h"
#include "C:\raylib\raylib\src\raylib.h"
#include "entity.h"
#include <vector>
using namespace std;

/*
Contains:
spaceship mover
spaceship shooter


*/

class Alien : public Entity
{
public:
    static int collions;
    Alien();
    int lastShotTime = 0;
    // extra variables to help in moving
    static bool moveRight;
    static bool moveLeft;
    void move(vector<Alien> &enemy);
    void shoot(Sound *shootSound);
    void UpdateBulletPosition(Entity &player, Sound *DamageTaken);
};

#endif
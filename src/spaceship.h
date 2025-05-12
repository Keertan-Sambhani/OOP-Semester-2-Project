#ifndef SPACESHIP
#define SPACESHIP
#include "bullet.h"
#include "C:\raylib\raylib\src\raylib.h"
#include "entity.h"
#include <vector>
#include "alien.h"

using namespace std;

/*
Contains:
spaceship mover
spaceship shooter


*/

class Spaceship : public Entity
{
public:
   Spaceship();
   void move();
   void shoot(Sound *shootSound);
   void UpdateBulletPosition(vector<Alien> &enemy, int &enemyCount);
};

#endif
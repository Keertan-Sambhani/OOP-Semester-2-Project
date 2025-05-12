#ifndef BULLET
#define BULLET
#include "C:\raylib\raylib\src\raylib.h"
class Entity;
class Spaceship;

/*When ever space bar is pressed a new instance of bullet is created(and the load and draw fucntion will be called) , the start position will be same the speed will be same and the damage will be same it's just a new object is created and temporarily stored in memory until it either collide with an object or the edge of the display*/

/*Space ship has bullets therefore it will be inside space ship object , each ship will have it's bullets*/

class Bullet
{
public:
    Vector2 bulletPosition;
    static Texture2D*BulletTexture;
    
    float bulletWidth, bulletHeight;
    Rectangle bulletRectangle;
    int speed = 14; // speed with which it's y coordinate changes
    int damage;    // empty until aliens are added

    Bullet(float scale, Entity*entity,float positionX);
    Bullet();
    void draw();
    Rectangle GetBulletRectangle();
    static void SetTxture(Texture2D *BulletTexture);
};

#endif
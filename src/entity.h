#ifndef ENTITY
#define ENTITY
#include "C:\raylib\raylib\src\raylib.h"
#include "bullet.h"
#include <vector>
using namespace std;
class Entity
{
public:
    Rectangle entityRectangle;
     double lastShotTime = 0.0;
    double shotCooldown = 0.45;

    float entityWidth, entityHeight; // will be initialized in the load texture function(scaling)
    int entityHealth;
    Vector2 entityPosition; // will be initialiized in the laod texture function
    vector<Bullet> bulletsShot;

    void draw(Texture2D *alien);
    void scaleEntityGraphic(float scale, float width, float height);

    // virtual void shoot() = 0;
    void setEntityPosition(Vector2 position);
    void scaleEntityGraphic(float scalingFactor);
    float getEntityWidht();
    float getEntityHeight();
    Rectangle GetEntityRectangle();
};

#endif
#include "bullet.h"
#include "C:\raylib\raylib\src\raylib.h"
#include "entity.h"

void Bullet::SetTxture(Texture2D *bulletTexture)
{
    Bullet::BulletTexture = bulletTexture;
}

Bullet::Bullet(float scale, Entity *entity,float positionX)
{

    bulletPosition = {
        positionX,
        entity->entityPosition.y - 40 // 20 pixels from bottom

    };
    bulletWidth = (*BulletTexture).width * scale;
    bulletHeight = (*BulletTexture).height * scale;
}

Texture2D *Bullet::BulletTexture = nullptr;
Bullet::Bullet()
{
}

void Bullet::draw()
{    
    // DrawRectangleLinesEx(this->GetBulletRectangle(), 2, RED);
    DrawTexturePro(
        (*BulletTexture),                                                                                           // the texture
        (Rectangle){0, 0, static_cast<float>((*BulletTexture).width), static_cast<float>((*BulletTexture).height)}, // how much of the origional image to use(here full)

        (Rectangle){bulletPosition.x, bulletPosition.y, bulletWidth, bulletHeight}, // destination=>  the position and scale of img
        (Vector2){0, 0},                                                            // this is the pivot point for the rotation
        0.0f,                                                                       // the actual rotation amount
        WHITE);
}

Rectangle Bullet::GetBulletRectangle()
{
    bulletRectangle = {bulletPosition.x+75, bulletPosition.y+75, bulletWidth-150, bulletHeight-125};
    return bulletRectangle;
}
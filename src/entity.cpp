#include "entity.h"
#include "C:\raylib\raylib\src\raylib.h"
#include "bullet.h"

void Entity::scaleEntityGraphic(float scale, float width, float height)
{
    // scale the image down according to given scaling factor
    entityWidth = width * scale;
    entityHeight = height * scale;

}

void Entity::draw(Texture2D *entityTexture)
{  
    //  DrawRectangleLinesEx(this->GetEntityRectangle(), 2, RED);
    DrawTexturePro(
        *entityTexture,                                                                                                   // the texture
        (Rectangle){0.0f, 0.0f, static_cast<float>((*entityTexture).width), static_cast<float>((*entityTexture).height)}, // how much of the original image to use (here full)

        (Rectangle){entityPosition.x, entityPosition.y, entityWidth, entityHeight}, // destination=>  the position and scale of img
        (Vector2){0, 0},                                                            // this is the pivot point for the rotation
        0.0f,                                                                       // the actual rotation amount
        WHITE);
    
}

void Entity::setEntityPosition(Vector2 position)
{
    entityPosition = position;
}
float Entity::getEntityWidht()
{
    return entityWidth;
}
float Entity::getEntityHeight()
{
    return entityHeight;
}


Rectangle Entity:: GetEntityRectangle(){
    entityRectangle={entityPosition.x,entityPosition.y,entityWidth,entityHeight};
    return entityRectangle;
}
#include "background.h"
#include "C:\raylib\raylib\src\raylib.h"



void Background::drawBackground(Texture2D*backgroundText)
{
    DrawTexture(*backgroundText, 0, 0, WHITE);
}

Background::~Background()
{
    UnloadTexture(backgroundImage);
}
#ifndef BACKGROUND
#define BACKGROUND
#include "C:\raylib\raylib\src\raylib.h"

/*
Contains:
NO CONSTRUCTOR
Background resources
Background Loader
Background Drawer
Background Unloader

*/
class Background
{
public:
    Texture2D backgroundImage;
    
    void drawBackground(Texture2D*backgroundText);
    ~Background();
};

#endif
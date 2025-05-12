#ifndef LEVEL
#define LEVEL

#include "C:\raylib\raylib\src\raylib.h"
#include "background.h"
#include "spaceship.h"
#include "bullet.h"
#include "alien.h"
#include "HighScore.h"
#include <iostream>
#include <vector>
using namespace std;

class Level
{
public:
    int NumberOfEnemiesPerRow = 8;
    int RowsOfEnemies = 4;
    int totalEnemies = NumberOfEnemiesPerRow * RowsOfEnemies;
    float AlienShootRate = 0.4;
    double lastAlienShotTime = 0;
    Vector2 StartingPlayerPosition;

    Vector2 alienPos;

    Spaceship player;
    Background background;
    vector<Alien> enemy;
    vector<Alien> backup_enemy;
    Texture2D *playerText, *AlienText, *Level_Background, *heart;
    Level(Texture2D *playerText, Texture2D *AlienText, Texture2D *Level_Background, Texture2D *heart);
    Level();
    void play(int &choice, highscore &InGameHighScore, string LevelNumber,Sound *lazerShot, Sound *enemyDeath, Sound *WinSound, Sound *LoseSound, Sound *DamageTaken, Music *loadingMusic, Music *music);
    void modifyLevel(int entityHealth)
    {
           
        
        totalEnemies = NumberOfEnemiesPerRow * RowsOfEnemies;
        for (int i = 0; i < totalEnemies; i++)
        {
            enemy[i].entityHealth = entityHealth;
        }

        backup_enemy = enemy;
    }
};

#endif
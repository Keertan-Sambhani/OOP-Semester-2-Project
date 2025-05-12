#include "C:\raylib\raylib\src\raylib.h"
#include "level.h"

Level::Level() {}
Level::Level(Texture2D *playerText, Texture2D *AlienText, Texture2D *Level_Background, Texture2D *heart) : enemy(totalEnemies), backup_enemy(totalEnemies)
{

    //-----------------
    this->playerText = playerText;
    this->AlienText = AlienText;
    this->Level_Background = Level_Background;
    this->heart = heart;

    player.scaleEntityGraphic(0.2, (*playerText).width, (*playerText).height);
    for (int i = 0; i < totalEnemies; i++)
        enemy[i].scaleEntityGraphic(0.11, (*AlienText).width, (*AlienText).height);
    // calculating and setting starting position
    int Screenwidth = GetScreenWidth();
    int Screenheight = GetScreenHeight();

    float height, width;
    height = player.getEntityHeight();
    width = player.getEntityWidht();
    StartingPlayerPosition = {
        (Screenwidth - height) / 2,
        Screenheight - width - 75 // 20 pixels from bottom
    };

    alienPos = {
        30, 60

    };

    player.setEntityPosition(StartingPlayerPosition);
    for (int j = 0, k = 0; j < RowsOfEnemies; j++)
    {

        for (int i = 0; i < NumberOfEnemiesPerRow; i++)
        {
            enemy[k++].setEntityPosition(alienPos);
            alienPos.x += 125;
        }
        alienPos.x = 30;
        alienPos.y += 100;
    }
    backup_enemy = enemy;
    //----------------------
    // scaling the texture (bullet will be scaled in it's constructor)
}

void Level::play(int &choice, highscore &InGameHighScore, string LevelNumber, Sound *lazerShot, Sound *enemyDeath, Sound *WinSound, Sound *LoseSound, Sound *DamageTaken, Music *loadingMusic, Music *music)
{
    int score = (32 - totalEnemies) * 1000; // each enemy killed will give a 1000 points
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw background
    background.drawBackground(Level_Background);

    // Draw scaled player at calculated position
    player.draw(playerText);
    player.shoot(lazerShot);

    player.UpdateBulletPosition(enemy, totalEnemies);
    player.move();
    for (auto it = enemy.begin(); it != enemy.end();)
    {
        if (it->entityHealth <= 0)
        {
            PlaySound(*enemyDeath);
            it = enemy.erase(it);
            totalEnemies--; // erase() returns next valid iterator
        }
        else
        {
            it->draw(AlienText);
            it->move(enemy);
            it->UpdateBulletPosition(player, DamageTaken);
            ++it;
        }
    }

    double currentTime = GetTime();
    if (((currentTime - lastAlienShotTime) >= AlienShootRate) && (totalEnemies > 0))
    {

        enemy[rand() % totalEnemies].shoot(lazerShot);
        lastAlienShotTime = currentTime;
    }

    for (int i = 0; i < player.entityHealth; i++)
    {
        DrawTexturePro(
            *heart,                                                                                           // the texture
            (Rectangle){0.0f, 0.0f, static_cast<float>((*heart).width), static_cast<float>((*heart).height)}, // how much of the original image to use (here full)

            (Rectangle){static_cast<float>(GetScreenWidth() - 75 - i * 50), GetScreenHeight() - 70.0f, (heart->width) * 0.07f, (heart->height) * 0.07f}, // destination=>  the position and scale of img
            (Vector2){0, 0},                                                                                                                             // this is the pivot point for the rotation
            0.0f,                                                                                                                                        // the actual rotation amount
            WHITE);
    }

    DrawText(TextFormat("Score:\t%d", score), 50, 20, 30, WHITE);
    DrawText(LevelNumber.c_str(), GetScreenWidth() - 150, 20, 30, WHITE);

    EndDrawing();
    for (int i = 0; i < totalEnemies; i++)
    {
        if (CheckCollisionRecs(enemy[i].GetEntityRectangle(), player.GetEntityRectangle()) || enemy[i].entityPosition.y >= GetScreenHeight() - enemy[i].entityHeight)
        {
            player.entityHealth = 0;
            break;
        }
    }

    if (player.entityHealth <= 0)
    {
        PlaySound(*LoseSound);
        // Lost
        choice = 4;
        InGameHighScore.addScore(score);
        InGameHighScore.write_data_to_file();
        player.setEntityPosition(StartingPlayerPosition);

        for (int i = 0; i < totalEnemies; i++)
        {
            enemy[i].bulletsShot.clear();
        }

        enemy = backup_enemy;
        totalEnemies = NumberOfEnemiesPerRow * RowsOfEnemies;
        player.entityHealth = 5;
        player.bulletsShot.clear();
        PauseMusicStream(*music);
        ResumeMusicStream(*loadingMusic);
    }
    if (totalEnemies == 0)
    { // Won
        PlaySound(*WinSound);
        enemy = backup_enemy;
        totalEnemies = NumberOfEnemiesPerRow * RowsOfEnemies;
        player.entityHealth = 5;
        player.bulletsShot.clear();
        InGameHighScore.addScore(score);
        InGameHighScore.write_data_to_file();
        player.setEntityPosition(StartingPlayerPosition);
        choice = 5;
        PauseMusicStream(*music);
        ResumeMusicStream(*loadingMusic);
    }
}
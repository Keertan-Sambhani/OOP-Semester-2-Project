#include "C:\raylib\raylib\src\raylib.h"
#include "background.h"
#include "spaceship.h"
#include "bullet.h"
#include "alien.h"
#include "Level.h"
#include "Game.h"
#include "HighScore.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

Game::Game()
{
}

void Game::SimulateGame()
{
    InGameHighScore.fetch_data_from_file();
    srand(time(0));

    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, "Fullscreen Example");
    InitAudioDevice();
    SetMasterVolume(1.0f);
    // loading the textures

    Texture2D playerText = LoadTexture("Resources/spaceship 1.png");
    Texture2D heart = LoadTexture("Resources/heart.png");
    Texture2D bulletText = LoadTexture("Resources/lazer shot.png");
    Texture2D MainMenu = LoadTexture("Resources/MainMenu.png");
    Texture2D scoreScreen = LoadTexture("Resources/HighScore Screen.png");
    Texture2D LostScreen = LoadTexture("Resources/GameOver.png");
    Texture2D WinScreen = LoadTexture("Resources/YOU WON.png");
    Texture2D LevelScreen = LoadTexture("Resources/Levels Options.jpg");
    Bullet::SetTxture(&bulletText); // passing to bullets as it has static variable
    // Level 1
    Texture2D AlienLeveL1 = LoadTexture("Resources/alien Level 1.png");
    Texture2D Level_1_Background = LoadTexture("Resources/LeveL1Background.jpg");

    // Level 2
    Texture2D playerTextLevl2 = LoadTexture("Resources/spaceship 2.png");
    Texture2D AlienLeveL2 = LoadTexture("Resources/alien Level 2.png");
    Texture2D Level_2_Background = LoadTexture("Resources/LeveL2Background.png");
    // Level 3

    Texture2D playerTextLevl3 = LoadTexture("Resources/spaceship 3.png");
    Texture2D AlienLeveL3 = LoadTexture("Resources/alien Level 3.png");
    Texture2D Level_3_Background = LoadTexture("Resources/LeveL3Background.jpg");
    // loading sound
    Sound AlienExplosion = LoadSound("Resources/explosion.ogg");
    Sound Lazer = LoadSound("Resources/laser.ogg");
    Sound WinSound = LoadSound("Resources/WinSound.wav");
    Sound LoseSound = LoadSound("Resources/loseSound.mp3");
    Sound ButtonPress = LoadSound("Resources/buttonPress.wav");
    Sound DamageTaken = LoadSound("Resources/DamageTaken.mp3");
    // Loding Music
    Music music = LoadMusicStream("Resources/MainTrack.mp3");
    Music LoadingMusic = LoadMusicStream("Resources/MenuTrack.mp3");

    SetTargetFPS(60);
    // Game Loop
    L1 = Level(&playerText, &AlienLeveL1, &Level_1_Background, &heart);
    L2 = Level(&playerTextLevl2, &AlienLeveL2, &Level_2_Background, &heart);
    L3 = Level(&playerTextLevl3, &AlienLeveL3, &Level_3_Background, &heart);
    L2.modifyLevel(3);
    L3.modifyLevel(4);
    PlayMusicStream(LoadingMusic);
    while ((!WindowShouldClose()) && (choice != 6))
    {
        if (choice == 7 || choice == 8 || choice == 9)
            UpdateMusicStream(music);
        else
            UpdateMusicStream(LoadingMusic);
        switch (choice)
        {
        case 1:
            ShowMainMenu(MainMenu, &ButtonPress, &LoadingMusic, &music);
            break;
        case 2:
            ShowLevelsScreen(LevelScreen, &ButtonPress, &LoadingMusic, &music);

            break;
        case 3:
            // score
            showHighScore(scoreScreen, &ButtonPress);
            break;
        case 4:
            // you lost
            if (IsKeyPressed(KEY_ENTER))
            {
                PlaySound(ButtonPress);
                choice = 1;
            }

            ShowLostScreen(LostScreen);
            break;
        case 5:
            // you won
              if (IsKeyPressed(KEY_ENTER))
            {
                PlaySound(ButtonPress);
                choice = 1;
            }

            ShowWinScreen(WinScreen);
            break;

        case 7:
            L1.play(choice, InGameHighScore, "Level: 1",&Lazer,&AlienExplosion,&WinSound,&LoseSound,&DamageTaken, &LoadingMusic, &music);
            break;
        case 8:
            L2.play(choice, InGameHighScore, "Level: 2",&Lazer,&AlienExplosion,&WinSound,&LoseSound,&DamageTaken, &LoadingMusic, &music);
            break;
        case 9:
            L3.play(choice, InGameHighScore, "Level: 3",&Lazer,&AlienExplosion,&WinSound,&LoseSound,&DamageTaken, &LoadingMusic, &music);

            break;
        }
    }
    StopMusicStream(LoadingMusic);
    StopMusicStream(music);
    UnloadMusicStream(LoadingMusic);
    UnloadMusicStream(music);

    CloseWindow();
}

void Game::ShowMainMenu(Texture2D &MainMenu, Sound *buttonPress, Music *loadingMusic, Music *music)
{
    Rectangle Start = {714, 526, 430, 121};
    Rectangle Score = {714, 696, 430, 121};
    Rectangle Quit = {714, 863, 430, 121};

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(MainMenu, 0, 0, WHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition(); // Returns {x, y} coordinates

        if (CheckCollisionPointRec(mousePos, Start))
        {
            PlaySound(*buttonPress);
            choice = 2;
            SetMusicVolume(*music, 0.5f);
        }
        if (CheckCollisionPointRec(mousePos, Score))
        {
            PlaySound(*buttonPress);
            choice = 3;
        }
        if (CheckCollisionPointRec(mousePos, Quit))
        {
            PlaySound(*buttonPress);
            choice = 6;
            InGameHighScore.write_data_to_file();
            // StopMusicStream(*MenuPageMusic);
        }
    }
    EndDrawing();
}
void Game::ShowLostScreen(Texture2D &LostScreen)
{

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(LostScreen, 0, 0, WHITE);

    if (IsKeyPressed(KEY_ENTER))
    {
        choice = 1;
    }
    EndDrawing();
}
void Game::ShowWinScreen(Texture2D &WinScreen)
{

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(WinScreen, 0, 0, WHITE);

    if (IsKeyPressed(KEY_ENTER))
    {
        choice = 1;
    }
    EndDrawing();
}
void Game::showHighScore(Texture2D &scoreScreen, Sound *buttonPress)
{
    InGameHighScore.fetch_data_from_file();
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(scoreScreen, 0, 0, WHITE);

    int x = 770, y = 431; // the starting position of the text n
    for (int i = 0; i < 10; i++)
    {
        if (i == 0)
            DrawText(TextFormat("%d   -   %d\n", i + 1, InGameHighScore.score[i]), x, y + (i * 40), 40, WHITE);
        else if (i == 9)
            DrawText(TextFormat("%d -   %d\n", i + 1, InGameHighScore.score[i]), x, y + (i * 40), 40, WHITE);
        else
        {

            DrawText(TextFormat("%d  -   %d\n", i + 1, InGameHighScore.score[i]), x, y + (i * 40), 40, WHITE);
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(*buttonPress);
        choice = 1;
    }
    EndDrawing();
}

void Game::ShowLevelsScreen(Texture2D &LevelsScreen, Sound *buttonPress, Music *loadingMusic, Music *music)
{ // arbitrary must be fixed
    Rectangle LeveL1 = {654, 424, 473, 121};
    Rectangle LeveL2 = {654, 596, 473, 121};
    Rectangle LeveL3 = {654, 762, 473, 121};

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(LevelsScreen, 0, 0, WHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition(); // Returns {x, y} coordinates

        if (CheckCollisionPointRec(mousePos, LeveL1))
        {
            choice = 7;
            PlaySound(*buttonPress);
            PauseMusicStream(*loadingMusic);
            PlayMusicStream(*music);
        }
        if (CheckCollisionPointRec(mousePos, LeveL2))
        {
            choice = 8;
            PlaySound(*buttonPress);
            PauseMusicStream(*loadingMusic);
            PlayMusicStream(*music);
        }
        if (CheckCollisionPointRec(mousePos, LeveL3))

        {
            choice = 9;
            PlaySound(*buttonPress);
            PauseMusicStream(*loadingMusic);
            PlayMusicStream(*music);
        }
    }
    EndDrawing();
}
#ifndef GAME
#define GAME
#include "HighScore.h"
#include"level.h"


class Game
{
public:
    int choice = 1;
    
    Level L1;
    Level L2;
    Level L3;
   

    highscore InGameHighScore;
    // methods
    Game();
    void SimulateGame();
    void ShowMainMenu(Texture2D &MainMenu,Sound *buttonPress, Music *loadingMusic, Music *music);
    void ShowWinScreen(Texture2D &WinScreen);
    void ShowLostScreen(Texture2D &LostScreen);
    void showHighScore(Texture2D &scoreScreen, Sound *buttonPress);
    void ShowLevelsScreen(Texture2D &LevelsScreen,Sound *buttonPress, Music *loadingMusic, Music *music);
};

#endif

#include "HighScore.h"
#include <iostream>
#include <fstream>
using namespace std;

highscore::highscore()
{

    for (int i = 0; i < MaxScoresStored; i++)
    {
        score[i] = 0;
    }
}

void highscore::fetch_data_from_file()
{
    ifstream file("Score_file.txt");
    if (file.is_open())
    {

        for (int i = 0; i < MaxScoresStored; i++)
        {
            file >> score[i];
        }

        file.close();
    }
    else
        cout << "File failed to open" << endl;
}

void highscore::write_data_to_file()
{
    ofstream file;
    file.open("Score_file.txt");
    if (file.is_open())
    {

        for (int i = 0; i < MaxScoresStored; i++)
        {
            file << score[i] << endl;
        }

        file.close();
    }
    else
        cout << "fialed to open file" << endl;
}

void highscore::addScore(int points)
{
    for (int i = 0; i < MaxScoresStored; i++)
    {
        if (points == score[i])
            return;
        if (points > score[i])
        {

            for (int j = MaxScoresStored - 1; j > i; j--)
            {
                score[j] = score[j - 1];
            }
            score[i] = points;
            return;
        }
    }
}

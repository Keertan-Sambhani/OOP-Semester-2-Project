#ifndef HIGHSCORE
#define HIGHSCORE

#define MaxScoresStored 10

class highscore
{
public:
    int score[MaxScoresStored];
    highscore();

    void fetch_data_from_file();

    void write_data_to_file();

    void addScore(int points);
};

#endif
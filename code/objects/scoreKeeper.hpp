#ifndef SCOREKEEPER
#define SCOREKEEPER

#include <iostream> 

struct ScoreKeeper{
    int m_playerScore = 0;
    int m_aiScore = 0;

    //The point from which players lose points. (Yellow LEDs)
    const int m_scorestealThreshold = 50;

    //The point from which players win. (Green LEDs)
    const int m_maxScore = 3;

    void addPoints(bool toPlayer);

    bool isLEDLit(bool isPlayer, int lightID);

    void reset();
};

#endif
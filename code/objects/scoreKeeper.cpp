#include <objects/scoreKeeper.hpp>

void ScoreKeeper::addPoints(bool toPlayer){
    if(toPlayer){
        m_playerScore += 1;
        if(m_aiScore >= m_scorestealThreshold){
            m_aiScore -= 1;
        }
    }
    else{
        m_aiScore += 1;
        if(m_playerScore >= m_scorestealThreshold){
            m_playerScore -= 1;
        }
    }

    if(m_playerScore = m_maxScore){
        std::printf("PLAYA WONNNNNN WHOOO\n");
    }
    else if(m_aiScore = m_maxScore){
        std::printf("AI WON WHOOOO not! fuck that ai >:[\n");
    }
}

bool ScoreKeeper::isLit(bool isPlayer, int lightID){
    if(isPlayer){
        if (lightID <= m_playerScore){
            return true;
        }
        return false;
    }
    else{
        if(lightID <= m_aiScore){
            return true;
        }
        return false;
    }
}
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
}

bool ScoreKeeper::isLEDLit(bool isPlayer, int lightID){
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

void ScoreKeeper::reset(){
    m_playerScore = 0;
    m_aiScore = 0;
}
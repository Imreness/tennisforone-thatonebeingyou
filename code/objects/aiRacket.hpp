#ifndef AIRACKET
#define AIRACKET
#include <objects/gameObject.hpp>
#include <random>

enum class AIDIFFICULTY{
    EASY,
    MEDIUM,
    HARD
};

struct aiRacket{
    GameObject& m_refObject;

    AIDIFFICULTY m_difficulty;

    glm::vec3 m_position;
    glm::vec3 m_targetPosition;
    float m_movementSpeed = 3;

    const float m_minSpeedEasy = 1.5f;
    const float m_maxSpeedEasy = 2.5f;
    const float m_minSpeedNormal = 3.f;
    const float m_maxSpeedNormal = 5.f;
    const float m_minSpeedHard = 5.5f;
    const float m_maxSpeedHard = 7.f;

    const float m_speedEasy = (m_minSpeedEasy + m_maxSpeedEasy) / 2;
    const float m_speedNormal = (m_minSpeedNormal + m_maxSpeedNormal) / 2;
    const float m_speedHard = (m_minSpeedHard + m_maxSpeedHard) / 2;

    //Side note:
    //This feature allows the game to be "easier" each time the player loses.
    //Only downside is that the effect has to be subtle AND the player may not have enough patience to wait for this value to rise.
    float m_difficultyBalance = 1;
    int m_amountOfTimesWon = 0;

    aiRacket(GameObject& refObject, AIDIFFICULTY difficulty);

    void update(double deltaTime);

    void changeSpeed();

    void changeDifficulty(AIDIFFICULTY newdiff);

    glm::vec3 generateRackedDir();

    void setTarget(glm::vec3 targetPos);

    void aiWon();

private:

    void clampPosition();

};

#endif
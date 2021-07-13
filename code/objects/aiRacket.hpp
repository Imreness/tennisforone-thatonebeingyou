#ifndef AIRACKET
#define AIRACKET
#include <objects/gameObject.hpp>

enum class AIDIFFICULTY{
    EASY,
    MEDIUM,
    HARD
};

struct aiRacket{
    GameObject& m_refObject;
    GameObject& m_refShock;

    AIDIFFICULTY m_difficulty;

    glm::vec3 m_position;
    glm::vec3 m_targetPosition;
    float m_movementSpeed = 3;

    //how much + / - max will be added to the ball's position
    float m_ballguessfailfactorMax = 0.1;

    aiRacket(GameObject& refObject, GameObject& refShock, AIDIFFICULTY difficulty);

    void update(double deltaTime);

    void setTarget(glm::vec3 targetPos);

private:

    void clampPosition();

};

#endif
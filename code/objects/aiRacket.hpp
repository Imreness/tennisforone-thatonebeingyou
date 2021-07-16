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
    GameObject& m_refShock;

    AIDIFFICULTY m_difficulty;

    glm::vec3 m_position;
    glm::vec3 m_targetPosition;
    float m_movementSpeed = 3;

    aiRacket(GameObject& refObject, GameObject& refShock, AIDIFFICULTY difficulty);

    void update(double deltaTime);

    void changeSpeed();

    glm::vec3 generateRackedDir();

    void setTarget(glm::vec3 targetPos);

private:

    void clampPosition();

};

#endif
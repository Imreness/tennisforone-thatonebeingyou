#ifndef PLAYERRACKET
#define PLAYERRACKET
#include <objects/gameObject.hpp>

struct playerRacket{

    GameObject& m_refObject;
    GameObject& m_refShock;

    glm::vec3 m_position;
    float m_angle;

    playerRacket(GameObject& refObject, GameObject& refShock);

    void move(glm::vec3 targetpos);

private:

    void clampPos();

    void processRotation();
};

#endif
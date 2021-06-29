#ifndef PLAYERRACKET
#define PLAYERRACKET
#include <objects/gameObject.hpp>

struct playerRacket{

    GameObject& m_refObject;

    glm::vec3 m_position;
    float m_angle;

    playerRacket(GameObject& refObject);

    void move(glm::vec3 targetpos);

private:

    void clampPos();

    void processRotation();
};

#endif
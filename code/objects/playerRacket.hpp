#ifndef PLAYERRACKET
#define PLAYERRACKET
#include <objects/gameObject.hpp>

struct playerRacket{

    GameObject& m_refObject;

    glm::vec3 m_position;

    //dont use this
    playerRacket(GameObject& refObject);
};

#endif
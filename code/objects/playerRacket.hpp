#ifndef PLAYERRACKET
#define PLAYERRACKET
#include <objects/gameObject.hpp>

enum class RACKETMOVEMENT{
    LEFT,
    RIGHT,
    SWITCHLEFT,
    SWITCHRIGHT
};

struct playerRacket{
    GameObject& m_refObject;

    glm::vec3 m_position;
    glm::vec3 m_targetPosition;
    float m_movementSpeed = 3;


    playerRacket(GameObject& refObject);

    void update (double deltaTime);

    void setTarget(glm::vec3 targetPos);

private:

    void clampPosition(); 

    void interpolatePosition(double deltaTime);

    void setModelValues(glm::mat4& ref);

};

#endif
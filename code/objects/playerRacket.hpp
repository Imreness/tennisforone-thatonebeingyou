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
    GameObject& m_refShock;

    glm::vec3 m_position;
    glm::vec3 m_targetPosition;
    float m_movementSpeed = 3;

    float m_angle = 0;
    float m_targetAngle = 0 ;
    float m_angleSpeed = 8;

    playerRacket(GameObject& refObject, GameObject& refShock);

    void update (double deltaTime);

    void setTarget(glm::vec3 targetPos);

    void rotate(RACKETMOVEMENT pos, double deltaTime);

private:

    void clampPosition(); 

    void interpolateRotation(double deltaTime);

    void interpolatePosition(double deltaTime);

    void setModelValues(glm::mat4& ref);

};

#endif
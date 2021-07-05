#ifndef TENNISBALL
#define TENNISBALL
#include <objects/gameObject.hpp>

struct tennisBall{
    GameObject& m_refBall;

    glm::vec3 m_position;
    glm::vec3 m_direction;
    float m_speed = 1;

    float m_currCooldown= 0;
    float m_cooldownMax = 0.3;

    tennisBall(GameObject& refBall);

    void update(float deltaTime);

    void reflect();
    void reflect(float racketSpeed, glm::vec3 hitpos, float distanceFromCenter);

    void resetBall(bool passToPlayer);    
};

#endif
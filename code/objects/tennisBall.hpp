#ifndef TENNISBALL
#define TENNISBALL
#include <objects/gameObject.hpp>

enum class WallTypes{
    FLOOR,
    RIGHT,
    LEFT,
    TOP,
    ENEMY,
    PLAYER
};

struct tennisBall{
    GameObject& m_refBall;
    GameObject& m_refShadow;

    glm::vec3 m_position;
    glm::vec3 m_direction;
    float m_speed = 1;
    const float m_maxSpeed = 2;

    float m_currCooldown= 0;
    float m_cooldownMax = 0.3;

    tennisBall(GameObject& refBall, GameObject& refShadow);

    void update(float deltaTime);

    void reflect(WallTypes hittype);
    void reflect(float racketSpeed, glm::vec3 ballpos, glm::vec3 racketCenter);

    void calculateShadowScale(float distanceFromGround);

    void resetBall(bool passToPlayer);    
};

#endif
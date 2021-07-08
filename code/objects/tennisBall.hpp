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
    GameObject& m_refGuide;

    glm::vec3 m_position;
    glm::vec3 m_direction;
    float m_speed = 2;
    float m_maxSpeed = 3.5f;
    float m_minSpeed = 2;
    float m_ballSpeedMultiplier = 5;

    float m_currCooldown= 0;
    float m_cooldownMax = 0.1;

    tennisBall(GameObject& refBall, GameObject& refShadow, GameObject& refGuide);

    void update(float deltaTime);

    void reflect(WallTypes hittype);
    void reflect(glm::vec3 racketDir);

    void calculateShadowScale(float distanceFromGround);
    void calculateGuideRing(float distanceFromBoard);

    void resetBall(bool passToPlayer);    
};

#endif
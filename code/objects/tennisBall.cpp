#include <objects/tennisBall.hpp>

tennisBall::tennisBall(GameObject& refBall)
    : m_refBall{refBall}{
    std::printf("ahaha\n");
}

void tennisBall::update(float deltaTime){
    m_position = glm::mix(m_position, m_position + m_direction, deltaTime * m_speed);

    m_refBall.m_modelMat = glm::mat4(1.);
    m_refBall.m_modelMat = glm::translate(m_refBall.m_modelMat, m_position);

    if(m_currCooldown >= 0){
        m_currCooldown -= deltaTime;
    }
}

void tennisBall::resetBall(bool passToPlayer){
    m_speed = 1;
    m_position = glm::vec3(3.4 , 0.945, 0);
    if(passToPlayer){
        m_direction = glm::vec3(-1 , 0 ,0);
    }
    else{
        m_direction = glm::vec3(1 , 0 ,0);
    }

}

void tennisBall::reflect(float racketSpeed, glm::vec3 hitpos, float distanceFromCenter){
    if(m_currCooldown < 0){
        m_currCooldown = m_cooldownMax;

        m_speed += racketSpeed / 10;

        m_direction = glm::reflect(m_direction, glm::vec3(1.,0,0));
        m_direction = glm::normalize(m_direction);
    }
}
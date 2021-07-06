#include <objects/tennisBall.hpp>

tennisBall::tennisBall(GameObject& refBall)
    : m_refBall{refBall}{
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

void tennisBall::reflect(float racketSpeed, glm::vec3 ballpos, glm::vec3 racketCenter){
    if(m_currCooldown < 0){
        m_currCooldown = m_cooldownMax;

        m_speed += racketSpeed / 5;

        glm::vec2 flatdir = glm::vec2(ballpos.z, ballpos.y) - glm::vec2(racketCenter.z, racketCenter.y);
        float dist = glm::distance(glm::vec2(ballpos.z, ballpos.y),glm::vec2(racketCenter.z, racketCenter.y));
        flatdir = glm::normalize(flatdir);

        //fixed number means the racket size is fix... not my proudest code lmao
        dist = dist / 1;

        std::printf("%f\n", dist);

        glm::vec3 normalvector = glm::mix(glm::vec3(1, 0 ,0), glm::vec3(0, flatdir.y, flatdir.x), dist);

        m_direction = glm::reflect(m_direction, normalvector);
        m_direction = glm::normalize(m_direction);
    }
}

void tennisBall::reflect(WallTypes hittype){

    m_speed += 0.5;

    glm::vec3 normalvector;

    switch (hittype){
        case WallTypes::FLOOR:
            normalvector = glm::vec3(0, 1. , 0);
            break;
        case WallTypes::TOP:
            normalvector = glm::vec3(0, -1. ,0);
            break;
        case WallTypes::LEFT:
            normalvector = glm::vec3(0, 0 ,-1);
            break;
        case WallTypes::RIGHT:
            normalvector = glm::vec3(0,0 ,1);
            break;
        case WallTypes::ENEMY:
            normalvector = glm::vec3(-1, 0 ,0);
            break;
        case WallTypes::PLAYER:
            normalvector = glm::vec3(1 , 0 ,0);
            break;
    }

    m_direction = glm::reflect(m_direction, normalvector);

    m_direction = glm::normalize(m_direction);

}
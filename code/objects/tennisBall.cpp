#include <objects/tennisBall.hpp>

tennisBall::tennisBall(GameObject& refBall, GameObject& refShadow, GameObject& refGuide)
    : m_refBall{refBall}, m_refShadow{refShadow}, m_refGuide{refGuide}{
    spdlog::info("Creating ball....");
}

void tennisBall::update(float deltaTime){
    m_position = glm::mix(m_position, m_position + m_direction, deltaTime * m_speed);

    m_refBall.m_modelMat = glm::mat4(1.);
    m_refBall.m_modelMat = glm::translate(m_refBall.m_modelMat, m_position);

    if(m_currCooldown >= 0){
        m_currCooldown -= deltaTime;
    }

    if(m_speed > m_maxSpeed){
        m_speed = m_maxSpeed;
    }
    else if(m_speed < m_minSpeed){
        m_speed = m_minSpeed;
    }
}

void tennisBall::resetBall(bool passToPlayer){
    m_lastWall = WallTypes::NONE;
    m_speed = m_minSpeed; 
    m_position = glm::vec3(3.4 , 0.945, 0);
    if(passToPlayer){
        m_direction = glm::vec3(-1 , 0 ,0);
    }
    else{
        m_direction = glm::vec3(1 , 0 ,0);
    }

}

void tennisBall::calculateShadowScale(float distanceFromGround){
    glm::mat4& mat = m_refShadow.m_modelMat;

    mat = glm::mat4(1.);
    glm::vec3 shadowpos = glm::vec3(m_position.x , 0, m_position.z);
    mat = glm::translate(mat , shadowpos);

    float shadowscale = distanceFromGround / 0.85;

    if(shadowscale < 1){
        shadowscale = 1;
    }

    mat = glm::scale(mat, glm::vec3(shadowscale));
}

void tennisBall::calculateGuideRing(float distanceFromBoard){
    glm::mat4& mat = m_refGuide.m_modelMat;

    if (distanceFromBoard < 0.1){
        distanceFromBoard = 0.1;
    }

    mat = glm::mat4(1.);
    mat = glm::translate(mat, glm::vec3(0, m_position.y, m_position.z));

    mat = glm::scale(mat, glm::vec3(distanceFromBoard  / 1.1));
}

//racketdir is NOT normalized
void tennisBall::reflect(glm::vec3 racketDir, bool isEnemy){
    if(m_currCooldown < 0){
        m_currCooldown = m_cooldownMax;

        float racketVelocity = glm::length(racketDir);

        m_speed += racketVelocity * m_ballSpeedMultiplier;

        glm::vec3 racketDirNormalized = glm::normalize(racketDir);

        //std::printf("%f\n", racketVelocity);

        glm::vec3 backvector;
        if(isEnemy){
            backvector = glm::vec3(-1, 0,0);
        }
        else{
            backvector = glm::vec3(1, 0 ,0);
        }

        glm::vec3 ballreflector = glm::mix(backvector, racketDirNormalized, racketVelocity / 5);

        m_direction = ballreflector;
        m_direction = glm::normalize(m_direction);

        m_lastWall = WallTypes::NONE;

        //std::printf("Ball Speed: %f\n", m_speed);
    }
}

void tennisBall::reflect(WallTypes hittype){

    if(hittype == m_lastWall){
        return;
    }

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
            m_speed += 0.8;
            break;
        case WallTypes::PLAYER:
            normalvector = glm::vec3(1 , 0 ,0);
            break;
    }

    m_direction = glm::reflect(m_direction, normalvector);

    m_direction = glm::normalize(m_direction);

    m_speed -= 0.2;

    m_lastWall = hittype; 

//    std::printf("----\nangle: %f\ndirection: %f %f %f\nnormal: %f %f %f\n", glm::dot(m_direction, normalvector),
//                    m_direction.x, m_direction.y, m_direction.z,
//                    normalvector.x, normalvector.y, normalvector.z);

}
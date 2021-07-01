#include <objects/playerRacket.hpp>

playerRacket::playerRacket(GameObject& refObject, GameObject& refShock) : m_refObject{refObject}, m_refShock{refShock}{
    m_refShock.m_render = false;
    m_position = glm::vec3(0.);
    m_targetPosition = glm::vec3(0.);
}

void playerRacket::setTarget(glm::vec3 targetPos){
    m_targetPosition = targetPos;
    clampPosition();
}

void playerRacket::rotate(RACKETMOVEMENT pos, double deltaTime){
    switch (pos){
        case RACKETMOVEMENT::RIGHT:
            m_targetAngle += 45;
            break;
        
        case RACKETMOVEMENT::LEFT:
            m_targetAngle -= 45;
            break;

        case RACKETMOVEMENT::SWITCHLEFT:
            m_targetAngle -= 180;
            break;
        case RACKETMOVEMENT::SWITCHRIGHT:
            m_targetAngle += 180;
            break;
    }
}

void playerRacket::update(double deltaTime){
    interpolateRotation(deltaTime);
    interpolatePosition(deltaTime);

    setModelValues(m_refObject.m_modelMat);
    setModelValues(m_refShock.m_modelMat);
}

void playerRacket::setModelValues(glm::mat4& ref){
    ref = glm::mat4(1.);

    std::printf("%fX %fY %fZ\n", m_position.x, m_position.y , m_position.z);

    ref = glm::translate(ref, m_position);
    ref = glm::rotate(ref, glm::radians(m_angle), glm::vec3(1, 0 ,0));
}

void playerRacket::interpolatePosition(double deltaTime){
    m_position = glm::mix(m_position, m_targetPosition, deltaTime * m_movementSpeed);
}

void playerRacket::interpolateRotation(double deltaTime){
    m_angle = glm::mix(m_angle, m_targetAngle, deltaTime * m_angleSpeed);
}

void playerRacket::clampPosition(){
    if(m_targetPosition.y < 0.51){
        m_targetPosition.y = 0.51;
    }
    else if(m_targetPosition.y > 1.3){
        m_targetPosition.y = 1.3;
    }

    if(m_targetPosition.z < -1.4){
        m_targetPosition.z = -1.4;
    }
    else if(m_targetPosition.z > 1.4){
        m_targetPosition.z = 1.4;
    }

}
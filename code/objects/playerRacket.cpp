#include <objects/playerRacket.hpp>

playerRacket::playerRacket(GameObject& refObject, GameObject& refShock) : m_refObject{refObject}, m_refShock{refShock}{
    m_refShock.m_render = true;
    m_position = glm::vec3(0.);
    m_targetPosition = glm::vec3(0.);
}

void playerRacket::setTarget(glm::vec3 targetPos){
    m_targetPosition = targetPos;
    clampPosition();
}

void playerRacket::update(double deltaTime){
    interpolatePosition(deltaTime);

    setModelValues(m_refObject.m_modelMat);
    setModelValues(m_refShock.m_modelMat);
}

void playerRacket::setModelValues(glm::mat4& ref){
    ref = glm::mat4(1.);

    //std::printf("%fX %fY %fZ\n", m_position.x, m_position.y , m_position.z);

    ref = glm::translate(ref, m_position);
}

void playerRacket::interpolatePosition(double deltaTime){
    m_position = glm::mix(m_position, m_targetPosition, deltaTime * m_movementSpeed);
}

void playerRacket::clampPosition(){
    if(m_targetPosition.y < -0.1){
        m_targetPosition.y = -0.1;
    }
    else if(m_targetPosition.y > 1.8){
        m_targetPosition.y = 1.8;
    }

    if(m_targetPosition.z < -2){
        m_targetPosition.z = -2;
    }
    else if(m_targetPosition.z > 2){
        m_targetPosition.z = 2;
    }
}
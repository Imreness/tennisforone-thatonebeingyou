#include <objects/aiRacket.hpp>

aiRacket::aiRacket(GameObject& refObject, GameObject& refShock, AIDIFFICULTY difficulty) : m_refObject(refObject), m_refShock(refShock), m_difficulty(difficulty){
    m_position = glm::vec3(0., 7., 0.);
    m_targetPosition = glm::vec3(0., 7., 0.); 
    switch(m_difficulty){
        case AIDIFFICULTY::EASY:
            m_movementSpeed = 1;
            break;
        
        case AIDIFFICULTY::MEDIUM:
            m_movementSpeed = 3.5f;
            break;

        case AIDIFFICULTY::HARD:
            m_movementSpeed = 5.5f;
            break;
    }
}

void aiRacket::update(double deltaTime){
    m_position = glm::mix(m_position, m_targetPosition, deltaTime * m_movementSpeed);

    glm::mat4 mat = glm::mat4(1.f);

    mat = glm::translate(mat, m_position);

    m_refObject.m_modelMat = mat;
    m_refShock.m_modelMat = mat;
}

void aiRacket::setTarget(glm::vec3 targetPos){
    m_targetPosition = targetPos;
    clampPosition();
}

void aiRacket::clampPosition(){
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
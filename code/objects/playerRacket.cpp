#include <objects/playerRacket.hpp>

playerRacket::playerRacket(GameObject& refObject) : m_refObject{refObject}{
}

void playerRacket::move(glm::vec3 targetpos){
    m_position = targetpos;

    //std::printf("%f %f\n" , m_position.z , m_position.y);

    clampPos();
    processRotation();

    m_refObject.m_modelMat = glm::mat4(1.);

    m_refObject.m_modelMat = glm::translate(m_refObject.m_modelMat, m_position);
    m_refObject.m_modelMat = glm::rotate(m_refObject.m_modelMat, glm::radians(m_angle), glm::vec3(1, 0, 0));
}

void playerRacket::clampPos(){
    if(m_position.z < -1.4){
        m_position.z = -1.4;
    }
    else if(m_position.z > 1.4){
        m_position.z = 1.4;
    }
    if(m_position.y < 0){
        m_position.y = 0;
    }
    else if(m_position.y > 1.35){
        m_position.y = 1.35;
    }
}

void playerRacket::processRotation(){
    m_angle = (60*m_position.z);
    if(m_angle > 0){
        m_angle -= (m_position.y * 20) * m_position.z;
    }
    else{
        m_angle -= (m_position.y * 20) * m_position.z;
    }
    std::printf("%f\n", m_angle);
}
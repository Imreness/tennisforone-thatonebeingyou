#include <objects/aiRacket.hpp>

aiRacket::aiRacket(GameObject& refObject, GameObject& refShock, AIDIFFICULTY difficulty) : m_refObject(refObject), m_refShock(refShock), m_difficulty(difficulty){
    spdlog::info("Creating AI Racket...");

    m_position = glm::vec3(0., 7., 0.);
    m_targetPosition = glm::vec3(0., 7., 0.);

    switch(m_difficulty){
        case AIDIFFICULTY::EASY:
            m_movementSpeed = m_speedEasy;
            break;
        
        case AIDIFFICULTY::MEDIUM:
            m_movementSpeed = m_speedNormal;
            break;

        case AIDIFFICULTY::HARD:
            m_movementSpeed = m_speedHard;
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

void aiRacket::changeSpeed(){
    std::random_device rd;
    std::mt19937 mt(rd());

    float minSpeed = 0, maxSpeed = 0;

    switch(m_difficulty){
        case AIDIFFICULTY::EASY:
            minSpeed = m_minSpeedEasy;
            maxSpeed = m_maxSpeedEasy;
            break;
        case AIDIFFICULTY::MEDIUM:
            minSpeed = m_minSpeedNormal;
            maxSpeed = m_maxSpeedNormal;
            break;
        case AIDIFFICULTY::HARD:
            minSpeed = m_minSpeedHard;
            maxSpeed = m_maxSpeedHard;
            break;
    }

    std::uniform_real_distribution<float> speedGen(minSpeed, maxSpeed);

    m_movementSpeed = speedGen(mt);
    //std::printf("New AI speed: %f\n", m_movementSpeed);
}

void aiRacket::changeDifficulty(AIDIFFICULTY newdiff){
    m_difficulty = newdiff;

    switch(m_difficulty){
        case AIDIFFICULTY::EASY:
            m_movementSpeed = m_speedEasy;
            break;
        
        case AIDIFFICULTY::MEDIUM:
            m_movementSpeed = m_speedNormal;
            break;

        case AIDIFFICULTY::HARD:
            m_movementSpeed = m_speedHard;
            break;
    }
}

glm::vec3 aiRacket::generateRackedDir(){
    std::random_device rd;
    std::mt19937 mt(rd());

    float minDistace = 0, maxDistance = 0;

    switch(m_difficulty){
        case AIDIFFICULTY::EASY:
            minDistace = 0.05f;
            maxDistance = 0.15f;
            break;
        case AIDIFFICULTY::MEDIUM:
            minDistace = 0.15f;
            maxDistance = 0.5f;
            break;
        case AIDIFFICULTY::HARD:
            minDistace = 0.5f;
            maxDistance = 1.2f;
            break;
    }

    //0 - left , 1 - right, 0 - up , 1 - down
    std::uniform_int_distribution<int> direction(0,1);
    std::uniform_real_distribution<float> distanceGen(minDistace, maxDistance);

    glm::vec3 returnedvec = glm::vec3(0);

    //lefty righty
    if(direction(mt) == 1){
        returnedvec.z = -(distanceGen(mt));
    }
    else{
        returnedvec.z = distanceGen(mt);
    }

    //uppy downy
    if(direction(mt) == 1){
        returnedvec.y = -(distanceGen(mt));
    }
    else{
        returnedvec.y = distanceGen(mt);
    }

    return returnedvec;
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
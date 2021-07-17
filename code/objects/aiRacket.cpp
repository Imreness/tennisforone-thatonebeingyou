#include <objects/aiRacket.hpp>

aiRacket::aiRacket(GameObject& refObject, GameObject& refShock, AIDIFFICULTY difficulty) : m_refObject(refObject), m_refShock(refShock), m_difficulty(difficulty){
    spdlog::info("Creating AI Racket...");

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

//speeds
/*
    1 - my grandma could win against this
    2 - really easy
    3 - same as player, but easy regardless
    4 - 
*/

void aiRacket::changeSpeed(){
    std::random_device rd;
    std::mt19937 mt(rd());

    float minSpeed = 0, maxSpeed = 0;

    switch(m_difficulty){
        case AIDIFFICULTY::EASY:
            minSpeed = 1.5f;
            maxSpeed = 2.5f;
            break;
        case AIDIFFICULTY::MEDIUM:
            minSpeed = 3.f;
            maxSpeed = 5.f;
            break;
        case AIDIFFICULTY::HARD:
            minSpeed = 5.5f;
            maxSpeed = 10.f;
            break;
    }

    
}

glm::vec3 aiRacket::generateRackedDir(){
    std::random_device rd;
    std::mt19937 mt(rd());

    float minDistace = 0, maxDistance = 0;

    switch(m_difficulty){
        case AIDIFFICULTY::EASY:
            minDistace = 0.1f;
            maxDistance = 0.3f;
            break;
        case AIDIFFICULTY::MEDIUM:
            minDistace = 0.3f;
            maxDistance = 0.8f;
            break;
        case AIDIFFICULTY::HARD:
            minDistace = 0.8f;
            maxDistance = 1.5f;
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
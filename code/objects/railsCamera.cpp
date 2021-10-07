#include <objects/railsCamera.hpp>
#include <spdlog/spdlog.h>
#include <glm/gtx/matrix_decompose.hpp>

RailsCamera::RailsCamera(GLFWwindow* window){
    spdlog::info("Creating Game Camera...");
    int winX, winY;
	glfwGetWindowSize(window, &winX, &winY);
	m_proj = glm::mat4(1.0); m_view = glm::mat4(1.0);
	m_proj = glm::perspective(45.f, (float)winX / (float)winY, 0.001f, 1000.f);

	m_position = glm::vec3(-1, 0.43 , 0); m_up = glm::vec3(0., 1., 0.);
    m_front = glm::vec3(0);

    m_view = glm::lookAt(m_position, glm::vec3(0, m_position.y, 0), m_up);
}

void RailsCamera::update(double delta){
    if(m_moveTime > 0){
        m_position = glm::mix(m_position, m_targetPosition, delta * m_moveSpeed);
        m_front = glm::mix(m_front, m_targetFront, delta * m_moveSpeed);
        m_view = glm::lookAt(m_position, m_front, m_up);
        m_moveTime -= delta;
    }
    else{
        m_targetPosition = m_position;
        m_targetFront = m_front;
    }
}

void RailsCamera::setInternalValues(){
    glm::vec3 scale;
    glm::quat rot;
    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(m_view, scale, rot, m_position, skew, perspective);
}

void RailsCamera::moveTo(glm::vec3 position, glm::vec3 lookAt, float moveTime){
    m_targetPosition = position;
    m_targetFront = lookAt;

    if(moveTime == 0){
        m_moveTime = 0;
        m_position = position;
        m_front = lookAt;
        m_view = glm::lookAt(m_position, m_front, m_up);
    }
    else{
        m_moveTime = moveTime;
    }
}
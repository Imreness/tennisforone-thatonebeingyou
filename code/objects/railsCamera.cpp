#include <objects/railsCamera.hpp>
#include <spdlog/spdlog.h>

RailsCamera::RailsCamera(GLFWwindow* window){
    spdlog::info("Creating Game Camera...");
    int winX, winY;
	glfwGetWindowSize(window, &winX, &winY);
	m_proj = glm::mat4(1.0); m_view = glm::mat4(1.0);
	m_proj = glm::perspective(45.f, (float)winX / (float)winY, 0.001f, 1000.f);

	m_position = glm::vec3(-1, 0.43 , 0); m_up = glm::vec3(0., 1., 0.);

    m_view = glm::lookAt(m_position, glm::vec3(0, m_position.y, 0), m_up);
    m_targetView = glm::lookAt(m_position, glm::vec3(0, m_position.y, 0), m_up);
}

void RailsCamera::update(double delta){
    if(m_moveTime > 0){
        m_view = glm::interpolate(m_view, m_targetView, (float)delta * m_moveSpeed);
        m_moveTime -= delta;
    }
    else{
        m_targetView = m_view;
    }
}

void RailsCamera::moveTo(glm::vec3 position, glm::vec3 lookAt, float moveTime){
    m_targetView = glm::lookAt(position, lookAt, m_up);

    if(moveTime == 0){
        m_moveTime = 0;
        m_view = m_targetView;
    }
    else{
        m_moveTime = moveTime;
    }
}
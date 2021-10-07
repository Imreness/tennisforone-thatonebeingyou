#ifndef RAILSCAMERA
#define RAILSCAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_interpolation.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct RailsCamera{

    GLFWwindow* m_window;

	glm::mat4 m_view;
	glm::mat4 m_proj;

	glm::vec3 m_position, m_front, m_up, m_right;

    float m_moveSpeed = 1;
    float m_moveTime = 5;
    glm::vec3 m_targetPosition, m_targetFront;

    RailsCamera(GLFWwindow* window);

    void moveTo(glm::vec3 position, glm::vec3 lookAt, float moveTime = 5);

    void update(double delta);

private:

    void setInternalValues();

};
#endif
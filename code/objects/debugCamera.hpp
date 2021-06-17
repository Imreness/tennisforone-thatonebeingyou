#ifndef DEBUGCAM
#define DEBUGCAM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct DebugCamera
{
	GLFWwindow* m_window;

	glm::mat4 m_view;
	glm::mat4 m_proj;

	glm::vec3 m_position, m_front, m_up, m_right;

	float m_mouseLastX = 0, m_mouseLastY = 0;
	float m_yaw = 0, m_pitch = 0;
	bool m_recalculateMouse = true;

	//Sensitivites
	float m_lookSens = 0.25, m_moveSens = 5.;

	bool m_sprinting = false;

	DebugCamera(GLFWwindow* window);

	void update(double delta);
};

#endif
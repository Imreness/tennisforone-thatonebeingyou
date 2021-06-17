#include <objects/debugCamera.hpp>

DebugCamera::DebugCamera(GLFWwindow* window) : m_window(window)
{
	int winX, winY;
	glfwGetWindowSize(window, &winX, &winY);
	m_proj = glm::mat4(1.0); m_view = glm::mat4(1.0);
	m_proj = glm::perspective(45.f, (float)winX / (float)winY, 0.001f, 100.f);

	m_position = glm::vec3(0., 0. , 0); m_up = glm::vec3(0., 1., 0.);
}

void DebugCamera::update(double delta)
{
	if (glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(m_window, &mouseX, &mouseY);
		
		if(m_recalculateMouse)
		{
			m_mouseLastX = mouseX;
			m_mouseLastY = mouseY;
			m_recalculateMouse = false;
		}

		float xOffset = mouseX - m_mouseLastX;
		float yOffset = m_mouseLastY - mouseY;

		xOffset *= m_lookSens;
		yOffset *= m_lookSens;

		m_yaw += xOffset;
		m_pitch += yOffset;

		if (m_pitch >= 89.f)
			m_pitch = 89.f;
		else if (m_pitch < -89.f)
			m_pitch = -89.f;

		m_mouseLastX = mouseX;
		m_mouseLastY = mouseY;

		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			m_sprinting = true;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
			m_sprinting = false;

		float movspeed = m_moveSens * delta;
		if (m_sprinting)
			movspeed *= 2;

		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
			m_position += m_front * movspeed;
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
			m_position -= m_front * movspeed;
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
			m_position += m_right * movspeed;
		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
			m_position -= m_right * movspeed;

		glm::vec3 front;

		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));

		front = glm::normalize(front);

		m_front = front;

		m_right = glm::normalize(glm::cross(m_front, m_up));

		m_view = glm::lookAt(m_position, m_position + m_front, m_up);
	}

	if(glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		m_recalculateMouse = true;

}
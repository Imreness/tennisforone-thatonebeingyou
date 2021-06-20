#include <core/inputManager.hpp>

void InputManager::init(GLFWwindow* window){
    m_window = window; 
}

void InputManager::registerKey(std::string name, int key, bool isSticky){
    m_keys.insert({name, keyStruct{.m_isSticky = isSticky, .m_key = key}});
}


bool InputManager::isPressed(std::string name){
    if(m_keys.at(name).m_isSticky){
        keyStruct& currKey = m_keys.at(name);

        if(!(currKey.m_justPressed) && glfwGetKey(m_window, currKey.m_key) == GLFW_PRESS){
            currKey.m_justPressed = true;
            return true;
        }
        else if(currKey.m_justPressed && glfwGetKey(m_window, currKey.m_key) == GLFW_RELEASE){
            currKey.m_justPressed = false;            
        }

        return false;
    }
    else{
        keyStruct currKey = m_keys.at(name);

        if(glfwGetKey(m_window, currKey.m_key) == GLFW_PRESS){
            return true;
        }
        else{
            return false;
        }
    }
}


void InputManager::deleteKey(std::string name){
    m_keys.erase(name); 
}
#ifndef INPUTMANAGER
#define INPUTMANAGER

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>

struct keyStruct{
    bool m_justPressed = false;
    bool m_isSticky;
    bool m_isMouse;

    int m_key;    
};

class InputManager{
private:
    std::unordered_map<std::string, keyStruct> m_keys;

    GLFWwindow* m_window;

public:
    InputManager(){}

    void init(GLFWwindow* window);

    void registerKey(std::string name,int key,bool isSticky = false, bool isMouse = false);

    bool isPressed(std::string name);

    void deleteKey(std::string name);

};

#endif
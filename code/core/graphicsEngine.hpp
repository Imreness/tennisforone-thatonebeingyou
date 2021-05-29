#ifndef GRAPHICSENGINE
#define GRAPHICSENGINE
#include <ui/uiManager.hpp>
#include <core/shader.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class graphicsEngine{
private:

    GLFWwindow* m_targetWindow;

    std::unordered_map<std::string, Shader> m_shaders;

public:
    void setTargetWindow(GLFWwindow*);

    void loadShader(const char*, bool = false);



    void renderStart();
    void renderEnd();
};

#endif
#ifndef GRAPHICSENGINE
#define GRAPHICSENGINE
#include <ui/uiManager.hpp>
#include <core/shader.hpp>
#include <ui/uiManager.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class graphicsEngine{
private:

    GLFWwindow* m_targetWindow;

    std::unordered_map<std::string, Shader*> m_shaders;



    float m_uiQuad[24] = {
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f };
    unsigned int m_uiVAO, m_uiVBO;

public:
    void setTargetWindow(GLFWwindow*);

    void initUi();

    void loadShader(const char*, bool = false);


    void renderUi(uiManager&);

    void renderStart();
    void renderEnd();

    ~graphicsEngine();
};

#endif
#ifndef GRAPHICSENGINE
#define GRAPHICSENGINE
#include <ui/uiManager.hpp>
#include <core/shader.hpp>
#include <core/texture.hpp>
#include <ui/uiManager.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <objects/debugCamera.hpp>
#include <objects/gameObject.hpp>
#include <objects/railsCamera.hpp>

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

    Shader* getShader(std::string name);

    void renderUi(uiManager&);

    void renderObjects(DebugCamera*, std::vector<Texture*>& ,std::unordered_map<std::string, GameObject>&);
    void renderObjects(RailsCamera*, std::vector<Texture*>& ,std::unordered_map<std::string, GameObject>&);
    void renderObjects(DebugCamera*, std::vector<Texture*>& ,GameObject&);
    void renderObjects(RailsCamera*, std::vector<Texture*>& ,GameObject&);

    void renderStart();
    void renderEnd();

    ~graphicsEngine();
};

#endif
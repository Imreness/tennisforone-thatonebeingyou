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

//Facilitates almost all rendering jobs
class graphicsEngine{
private:

    GLFWwindow* m_targetWindow;

    std::unordered_map<std::string, Shader*> m_shaders;

    //Deprecated feature, but this was used to render the UI
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

    //Sidenote:
    //This "batch" rendering type of deal is really rigid. While its probably one of the fastest way of rendering objects,
    //for it to be applicable for a wide range of object types and shaders, it really needs to be made into a data-oriented design.
    //either via a scirpting language or just probably writing a few .JSON files to tell the game how to render things.

    void renderObjects(DebugCamera*, std::vector<Texture*>& ,std::unordered_map<std::string, GameObject>&, std::string shaderName = "object");
    void renderObjects(RailsCamera*, std::vector<Texture*>& ,std::unordered_map<std::string, GameObject>&, std::string shaderName = "object");
    void renderObjects(DebugCamera*, std::vector<Texture*>& ,GameObject&, std::string shaderName = "object");
    void renderObjects(RailsCamera*, std::vector<Texture*>& ,GameObject&, std::string shaderName = "object");

    //Sidenote:
    //An example of rigidity. This probably could've been a .JSON file used with the previous functions.
    //Also, originally the score lights were actual LED lightbulbs! Even if in game its now an LCD display,
    //the code still has the "light" name in it.

    void renderLight(DebugCamera*, std::vector<Texture*>&, GameObject&, bool isOn);
    void renderLight(RailsCamera*, std::vector<Texture*>&, GameObject&, bool isOn);

    void renderStart();
    void renderEnd();

    ~graphicsEngine();
};

#endif
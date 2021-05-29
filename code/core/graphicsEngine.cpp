#include <core/graphicsEngine.hpp>

void graphicsEngine::setTargetWindow(GLFWwindow* window){
    m_targetWindow = window;
}

void graphicsEngine::loadShader(const char* shaderName, bool hasGeo){
    if(hasGeo){
        std::string vertexName("shaders/"); vertexName.append(shaderName); vertexName.append(".vert");
        std::string fragmentName("shaders/"); fragmentName.append(shaderName); fragmentName.append(".frag");
        std::string geoName("shaders/"); geoName.append(shaderName); geoName.append(".geo");
        Shader shader{vertexName, fragmentName, geoName};
        m_shaders.insert({std::string(shaderName), shader});
    }
    else{
        std::string vertexName("shaders/"); vertexName.append(shaderName); vertexName.append(".vert");
        std::string fragmentName("shaders/"); fragmentName.append(shaderName); fragmentName.append(".frag");
        Shader shader{vertexName, fragmentName};
        m_shaders.insert({std::string(shaderName), shader});
    }
}

void graphicsEngine::renderStart(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1, 0.1 ,0.1 , 1.);
}

void graphicsEngine::renderEnd(){
    glfwSwapBuffers(m_targetWindow);
    glfwPollEvents();
}
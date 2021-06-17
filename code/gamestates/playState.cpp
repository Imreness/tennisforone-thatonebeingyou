#include <gamestates/playState.hpp>
#include <spdlog/spdlog.h>
#include <core/configloader.hpp>

void playState::init(GLFWwindow* referencewindow){
    spdlog::info("Launching play state...");

    m_window = referencewindow;
    initGraphics();
}

void playState::calculateDeltaTime(){
    float currTime = glfwGetTime();
    m_deltaTime = currTime - m_lastTime;
    m_lastTime = currTime;
}

void playState::initGraphics(){
    spdlog::info("Initalizing graphics engine");
    m_graphics.setTargetWindow(m_window);
    m_graphics.loadShader("debug");

    glEnable(GL_DEPTH_TEST);

    m_debugCam = new DebugCamera(m_window);

    assetLoader::loadAssetBundle(m_textures, m_models, "gameplay");
    initObjects();
}

void playState::initObjects(){
    for(const auto& object : m_models){
        m_gameObjects.push_back(GameObject(object.second));
    }
}

void playState::render(){
    m_graphics.renderStart();

    m_graphics.renderObjects(m_debugCam, m_textures, m_gameObjects);    

    m_graphics.renderEnd();
}

void playState::process(){
    calculateDeltaTime();

    m_debugCam->update(m_deltaTime);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    render();
}

bool playState::shouldRun(){
    return !glfwWindowShouldClose(m_window);
}

nextStateEnum playState::nextState(){
    if(glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS){
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return nextStateEnum::MENU;
    }
    else{
        return nextStateEnum::NOTHING;
    }
}

playState::~playState(){
    delete m_debugCam;
}
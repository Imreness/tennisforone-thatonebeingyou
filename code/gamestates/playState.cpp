#include <gamestates/playState.hpp>
#include <spdlog/spdlog.h>
#include <core/configloader.hpp>

void playState::init(GLFWwindow* referencewindow){
    spdlog::info("Launching play state...");

    m_window = referencewindow;
    initGraphics();
}

void playState::initGraphics(){
    spdlog::info("Initalizing graphics engine");
    m_graphics.setTargetWindow(m_window);

    m_graphics.loadShader("debug");

    assetLoader::loadAssetBundle(m_textures, m_models, "gameplay");
}

void playState::render(){
    m_graphics.renderStart();

    for(const auto& object : m_models){
        object.second->render();
    }

    m_graphics.renderEnd();
}

void playState::process(){
    render();
}

bool playState::shouldRun(){
    return !glfwWindowShouldClose(m_window);
}

nextStateEnum playState::nextState(){
    if(glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS){
        return nextStateEnum::MENU;
    }
    else{
        return nextStateEnum::NOTHING;
    }
}

playState::~playState(){
    
}
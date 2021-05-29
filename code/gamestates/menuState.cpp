#include <gamestates/menuState.hpp>
#include <spdlog/spdlog.h>

void menuState::init(GLFWwindow* referencewindow){
    spdlog::info("Launching main menu...");

    m_window = referencewindow;
    initGraphics();
}

void menuState::initGraphics(){
    spdlog::info("Initalizing graphics engine");
    m_graphics.setTargetWindow(m_window);

    m_graphics.loadShader("debug");
    m_graphics.loadShader("ui");

    initUI();
}
void menuState::initUI(){
    spdlog::info("Initalizing UI");

    m_uiManager.m_textures = assetLoader::loadUiPackage("mainmenu");
    m_graphics.initUi();
}

void menuState::render(){
    m_graphics.renderStart();

    m_graphics.renderUi(m_uiManager);

    m_graphics.renderEnd();
}

void menuState::process(){
    render();
}

void menuState::cleanup(){

}

bool menuState::shouldRun(){
    return !glfwWindowShouldClose(m_window);
}
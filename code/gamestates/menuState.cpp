#include <gamestates/menuState.hpp>
#include <spdlog/spdlog.h>
#include <core/configloader.hpp>

void menuState::init(GLFWwindow* referencewindow){
    spdlog::info("Launching main menu...");

    m_window = referencewindow;
    initGraphics();
}

void menuState::initGraphics(){
    spdlog::info("Initalizing graphics engine...");
    m_graphics.setTargetWindow(m_window);

    m_graphics.loadShader("object");
    m_graphics.loadShader("ui");

    initUI();
}

void menuState::initUI(){
    spdlog::info("Initalizing UI...");
    configStruct conf = config::loadConfig("game.conf");
    m_uiManager.m_screenHeight = conf.windowHeight;    
    m_uiManager.m_screenWidth = conf.windowWidth;    

    m_uiManager.setup("mainmenu");
    m_graphics.initUi();
}

void menuState::processUIClick(){
    if(m_uiManager.m_hovered_button == "exit" && glfwGetMouseButton(m_window, 0) == GLFW_PRESS){
        glfwSetWindowShouldClose(m_window, 1);
    }
    else if(m_uiManager.m_hovered_button == "play" && glfwGetMouseButton(m_window, 0) == GLFW_PRESS){
        m_startGame = true;
    }
}


void menuState::render(){
    m_graphics.renderStart();

    m_graphics.renderUi(m_uiManager);

    m_graphics.renderEnd();
}

void menuState::process(){
    double x,y;
    glfwGetCursorPos(m_window, &x, &y);
    m_uiManager.update((int)x,(int)y);
    processUIClick();

    render();
}

bool menuState::shouldRun(){
    return !glfwWindowShouldClose(m_window);
}

nextStateEnum menuState::nextState(){
    if(m_startGame){
        return nextStateEnum::INTRO;
    }
    else{
        return nextStateEnum::NOTHING;
    }
}

menuState::~menuState(){
   spdlog::info("Deleting menustate..."); 
}
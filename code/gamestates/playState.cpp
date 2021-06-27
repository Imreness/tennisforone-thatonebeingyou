#include <gamestates/playState.hpp>
#include <spdlog/spdlog.h>
#include <core/configloader.hpp>

void playState::init(GLFWwindow* referencewindow){
    spdlog::info("Launching play state...");

    m_window = referencewindow;
    m_physics.init(m_window);
    m_physics.initDebugDrawer();

    initGraphics();

    initObjects(); 

    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    initInput();
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
    m_graphics.loadShader("bulletDebug");

    glEnable(GL_DEPTH_TEST);

    m_debugCam = new DebugCamera(m_window);
    m_gameCam = new RailsCamera(m_window);
    m_gameCam->m_moveSpeed = 1;

    assetLoader::loadAssetBundle(m_textures, m_models, "gameplay");
}

void playState::initObjects(){
    m_gameObjects.insert({"playerRacket" , GameObject{m_models.at("racket")}});
    m_playerRacket = new playerRacket(m_gameObjects.at("playerRacket"));

    m_physics.createColObject("downbox");
    m_physics.addBoxCollider("downbox", reactphysics3d::Vector3(0.5,0.5,0.5), reactphysics3d::Vector3(0, -1,0));

    m_physics.createColObject("upbox");
    m_physics.addBoxCollider("upbox", reactphysics3d::Vector3(0.5,0.5,0.5), reactphysics3d::Vector3(0, 2,0));
}

void playState::render(){
    m_graphics.renderStart();

    if(m_debugMode){
        m_graphics.renderObjects(m_debugCam, m_textures, m_gameObjects);

        m_physics.update(m_deltaTime);
        m_physics.debugRender(m_debugCam->m_view, m_debugCam->m_proj, m_graphics.getShader("bulletDebug"));
    }
    else{
        m_graphics.renderObjects(m_gameCam, m_textures, m_gameObjects);
    }

    m_graphics.renderEnd();
}

void playState::process(){
    calculateDeltaTime();


    //std::printf("%b", m_physics.)

    if(m_debugMode){
        m_debugCam->update(m_deltaTime);
    }
    else{
        m_gameCam->update(m_deltaTime);
    }

    processInput();

    render();
}

void playState::initInput(){
    m_input.init(m_window);

    m_input.registerKey("debugMode", GLFW_KEY_F1, true);
}

void playState::processInput()
{
    if(m_input.isPressed("debugMode")){
        if(m_debugMode){
            m_debugMode = false;
        }
        else{
            m_debugMode = true;
        }
    }
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
   delete m_playerRacket;
   delete m_gameCam;
}
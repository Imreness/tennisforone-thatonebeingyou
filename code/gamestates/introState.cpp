#include <gamestates/introState.hpp>
#include <spdlog/spdlog.h>

void introState::init(GLFWwindow* referenceWindow){
    spdlog::info("Launching intro state...");

    m_window = referenceWindow;

    initGraphics();

    initObjects();
    initAudio();

    initInput();

    initCameraPath();

    initDeltaTime();
}

void introState::process(){
    calculateDeltaTime();

    m_gameCam->update(m_deltaTime);

    processFading();
    processInput();
    update3DAudio();
    processExitTimer();


    render();

}

bool introState::shouldRun(){
    return !glfwWindowShouldClose(m_window);
}

nextStateEnum introState::nextState(){
    if(m_exit){
        return nextStateEnum::GAME;
    }
    else{
        return nextStateEnum::NOTHING;
    }
}

void introState::initGraphics(){
    spdlog::info("Inintalizing graphics engine...");

    int windowWidth = 0, windowHeight = 0;
    glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

    m_graphics.setTargetWindow(m_window);
    m_graphics.loadShader("object");
    m_graphics.loadShader("framebuffer");

    m_frameBuffer = new FrameBuffer(windowWidth, windowHeight, windowWidth, windowHeight, m_graphics.getShader("framebuffer"));

    m_gameCam = new RailsCamera(m_window);
    m_gameCam->moveTo(glm::vec3(0, 0 , -5), glm::vec3(0 , 0 , 0), 0);
    m_gameCam->m_moveSpeed = 5;

    assetLoader::loadAssetBundle(m_textures, m_models, "intro");
}

void introState::initCameraPath(){
    m_cameraTargets = loadCameraPath("assets/intro.path");
}

void introState::initObjects(){
    spdlog::info("Initalizing Game Objects...");

    m_gameObjects.insert({"grass" , GameObject{m_models.at("grass")}});
}

void introState::render(){
    if(m_renderAccumulator > m_renderTick){
        m_frameBuffer->Bind();
        m_graphics.renderStart();

        m_graphics.renderObjects(m_gameCam, m_textures, m_gameObjects);

        m_graphics.renderEnd();

        m_frameBuffer->Render(m_brightness);

        m_renderAccumulator -= m_renderTick;
    }
    else{
        m_renderAccumulator += m_deltaTime;
    }
}

void introState::processFading(){
    if (m_fadeOut){
        if(m_brightness > 0){
            m_brightness -= m_deltaTime * m_fadeSpeed;
        }
        else{
            m_brightness = 0;
        }
    }
    else{
        if(m_brightness < 1){
            m_brightness += m_deltaTime * m_fadeSpeed;
        }
        else{
            m_brightness = 1;
        }
    }
}

void introState::processExitTimer(){
    if(m_exitTimerStart){
        m_exitTimer -= m_deltaTime;
        if(m_exitTimer <= 0){
            m_exit = true;
        }
    }
}

void introState::initInput(){
    spdlog::info("Initalizing Input...");

    m_input.init(m_window);

    glfwSetWindowUserPointer(m_window, this);

    m_input.registerKey("next", GLFW_KEY_SPACE, true);
}

void introState::processInput(){
    if(m_input.isPressed("next")){
        m_exitTimerStart = true;
        m_fadeOut = true;
    }
}

void introState::initAudio(){
    m_soloud = new SoLoud::Soloud;
    m_soloud->init();
}

void introState::update3DAudio(){
    m_soloud->set3dListenerParameters(
        m_gameCam->m_position.x , m_gameCam->m_position.y, m_gameCam->m_position.z,
        m_gameCam->m_front.x, m_gameCam->m_front.y, m_gameCam->m_front.z,
        m_gameCam->m_up.x , m_gameCam->m_up.y , m_gameCam->m_up.z
    );
}

introState::~introState(){
    spdlog::info("Deleting playstate...");

    m_soloud->deinit();

    delete m_gameCam;
}

void introState::initDeltaTime(){
    m_lastTime = glfwGetTime();   
}

void introState::calculateDeltaTime(){
    float currTime = glfwGetTime();
    m_deltaTime = currTime - m_lastTime;
    m_lastTime = currTime;
}
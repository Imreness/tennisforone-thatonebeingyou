#include <gamestates/menuState.hpp>
#include <spdlog/spdlog.h>

void menuState::init(GLFWwindow* referenceWindow){
    spdlog::info("Launching intro state...");

    m_window = referenceWindow;

    initCameraPath();
    initGraphics();

    initObjects();
    initAudio();

    initInput();

    initDeltaTime();
}

void menuState::process(){
    calculateDeltaTime();

    m_gameCam->update(m_deltaTime);

    processFading();
    processInput();
    update3DAudio();


    render();

}

bool menuState::shouldRun(){
    return !glfwWindowShouldClose(m_window);
}

nextStateEnum menuState::nextState(){
    if(m_exit){
        return nextStateEnum::INTRO;
    }
    else{
        return nextStateEnum::NOTHING;
    }
}

void menuState::initGraphics(){
    spdlog::info("Inintalizing graphics engine...");

    int windowWidth = 0, windowHeight = 0;
    glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

    m_graphics.setTargetWindow(m_window);
    m_graphics.loadShader("object");
    m_graphics.loadShader("framebuffer");

    m_frameBuffer = new FrameBuffer(windowWidth, windowHeight, windowWidth, windowHeight, m_graphics.getShader("framebuffer"));

    m_gameCam = new RailsCamera(m_window);
    m_gameCam->moveTo(m_cameraTargets.at(0).cameraPos, m_cameraTargets.at(0).cameraLookAt, 0);
    m_gameCam->m_moveSpeed = 5;

    assetLoader::loadAssetBundle(m_textures, m_models, "intro");
}

void menuState::initCameraPath(){
    m_cameraTargets = loadCameraPath("assets/intro.path");
}

void menuState::initObjects(){
    spdlog::info("Initalizing Game Objects...");

    m_gameObjects.insert({"brick" , GameObject{m_models.at("brick")}});
    m_gameObjects.insert({"Cube", GameObject{m_models.at("Cube")}});
}

void menuState::render(){
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

void menuState::processFading(){
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

void menuState::initInput(){
    spdlog::info("Initalizing Input...");

    m_input.init(m_window);

    glfwSetWindowUserPointer(m_window, this);

    m_input.registerKey("click", 0, true, true);
    m_input.registerKey("skipEsc", GLFW_KEY_ESCAPE, true);
    m_input.registerKey("skipSpace", GLFW_KEY_SPACE, true);
}

void menuState::processInput(){
    if(m_input.isPressed("next")){
    }
    if(m_input.isPressed("skipEsc") || m_input.isPressed("skipSpace")){
        //TODO
        //do some cameratarget translations like in introstate
    }
}

void menuState::initAudio(){
    m_soloud = new SoLoud::Soloud;
    m_soloud->init();
}

void menuState::update3DAudio(){
    m_soloud->set3dListenerParameters(
        m_gameCam->m_position.x , m_gameCam->m_position.y, m_gameCam->m_position.z,
        m_gameCam->m_front.x, m_gameCam->m_front.y, m_gameCam->m_front.z,
        m_gameCam->m_up.x , m_gameCam->m_up.y , m_gameCam->m_up.z
    );
}

menuState>:~menuState(){
    spdlog::info("Deleting playstate...");

    m_soloud->deinit();

    delete m_gameCam;
}

void menuState::initDeltaTime(){
    m_lastTime = glfwGetTime();   
}

void menuState::calculateDeltaTime(){
    float currTime = glfwGetTime();
    m_deltaTime = currTime - m_lastTime;
    m_lastTime = currTime;
}
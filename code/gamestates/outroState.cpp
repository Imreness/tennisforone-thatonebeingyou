#include <gamestates/outroState.hpp>
#include <spdlog/spdlog.h>

void outroState::init(GLFWwindow* referenceWindow){
    spdlog::info("Launching outro state...");

    m_window = referenceWindow;

    initCameraPath();
    initGraphics();

    initObjects();
    initAudio();

    initInput();

    initDeltaTime();
}

void outroState::process(){
    calculateDeltaTime();

    m_gameCam->update(m_deltaTime);

    processFading();
    processInput();
    update3DAudio();
    processExitTimer();


    render();

}

bool outroState::shouldRun(){
    return !glfwWindowShouldClose(m_window);
}

nextStateEnum outroState::nextState(){
    if(m_exit){
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return nextStateEnum::MENU;
    }
    else{
        return nextStateEnum::NOTHING;
    }
}

void outroState::initGraphics(){
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

void outroState::initCameraPath(){
    m_cameraTargets = loadCameraPath("assets/outro.path");
}

void outroState::initObjects(){
    spdlog::info("Initalizing Game Objects...");

    m_gameObjects.insert({"floor" , GameObject{m_models.at("floor")}});
    m_gameObjects.insert({"cagedecorfrontleft" , GameObject{m_models.at("cagedecorfrontleft")}});
    m_gameObjects.insert({"cagedecorfrontright" , GameObject{m_models.at("cagedecorfrontright")}});
    m_gameObjects.insert({"cagedecorrearleft" , GameObject{m_models.at("cagedecorrearleft")}});
    m_gameObjects.insert({"cagedecorrearright" , GameObject{m_models.at("cagedecorrearright")}});
    m_gameObjects.insert({"pathwayedge1" , GameObject{m_models.at("pathwayedge1")}});
    m_gameObjects.insert({"pathwayedge2" , GameObject{m_models.at("pathwayedge2")}});
    m_gameObjects.insert({"pathways" , GameObject{m_models.at("pathways")}});
    m_gameObjects.insert({"counterrack" , GameObject{m_models.at("counterrack")}});
    m_gameObjects.insert({"hedge1" , GameObject{m_models.at("hedge1")}});
    m_gameObjects.insert({"hedge2" , GameObject{m_models.at("hedge2")}});
    m_gameObjects.insert({"hedge3" , GameObject{m_models.at("hedge3")}});
    m_gameObjects.insert({"hedge4" , GameObject{m_models.at("hedge4")}});
    m_gameObjects.insert({"hedge5" , GameObject{m_models.at("hedge5")}});
    m_gameObjects.insert({"hedge6" , GameObject{m_models.at("hedge6")}});
    m_gameObjects.insert({"hedgevertical" , GameObject{m_models.at("hedgevertical")}});
    m_gameObjects.insert({"laser" , GameObject{m_models.at("laser")}});
    m_gameObjects.insert({"laser2" , GameObject{m_models.at("laser2")}});
    m_gameObjects.insert({"laser3" , GameObject{m_models.at("laser3")}});
    m_gameObjects.insert({"laser4" , GameObject{m_models.at("laser4")}});
    m_gameObjects.insert({"laser5" , GameObject{m_models.at("laser5")}});
    m_gameObjects.insert({"laser6" , GameObject{m_models.at("laser6")}});
    m_gameObjects.insert({"laser7" , GameObject{m_models.at("laser7")}});
    m_gameObjects.insert({"laser8" , GameObject{m_models.at("laser8")}});
    m_gameObjects.insert({"sky" , GameObject{m_models.at("sky")}});
    m_gameObjects.insert({"skyline" , GameObject{m_models.at("skyline")}});

    m_gameObjects.insert({"tp_wall", GameObject{m_models.at("tp_wall")}});
    m_gameObjects.insert({"tutorial1", GameObject{m_models.at("tutorial1")}});
    m_gameObjects.insert({"tutorial2", GameObject{m_models.at("tutorial2")}});
    m_gameObjects.insert({"tutorial3", GameObject{m_models.at("tutorial3")}});

    m_gameObjects.insert({"blood", GameObject{m_models.at("blood")}});
    m_gameObjects.insert({"legs", GameObject{m_models.at("legs")}});

    m_gameObjects.insert({"flier1", GameObject{m_models.at("flier1")}});
    m_gameObjects.insert({"flier2", GameObject{m_models.at("flier2")}});
    m_gameObjects.insert({"flier3", GameObject{m_models.at("flier3")}});
    m_gameObjects.insert({"flier4", GameObject{m_models.at("flier4")}});
    m_gameObjects.insert({"flier5", GameObject{m_models.at("flier5")}});
    
}

void outroState::render(){
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

void outroState::processFading(){
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
            if(m_fadeDelayTimer > 0){
                m_fadeDelayTimer -= m_deltaTime;
            }
            else{
                m_brightness += m_deltaTime * m_fadeSpeed;
            }
        }
        else{
            m_brightness = 1;
        }
    }
}

void outroState::processExitTimer(){
    if(m_exitTimerStart){
        m_exitTimer -= m_deltaTime;
        if(m_exitTimer <= 0){
            m_exit = true;
        }
    }
}

void outroState::initInput(){
    spdlog::info("Initalizing Input...");

    m_input.init(m_window);

    glfwSetWindowUserPointer(m_window, this);

    m_input.registerKey("next", GLFW_KEY_ESCAPE, true);
    m_input.registerKey("nextCamPos", GLFW_KEY_SPACE, true);
}

void outroState::processInput(){
    if(m_input.isPressed("next")){
        m_exitTimerStart = true;
        m_fadeOut = true;
    }
    if(m_input.isPressed("nextCamPos")){
        if(m_currentCameraTarget >= (m_cameraTargets.size() - 1)){
            m_exitTimerStart = true;
            m_fadeOut = true;
            return;
        }

        m_currentCameraTarget++;
        cameraTargetObject target = m_cameraTargets.at(m_currentCameraTarget);
        m_gameCam->m_moveSpeed = target.movementSpeed;
        m_gameCam->moveTo(target.cameraPos, target.cameraLookAt, target.movementTime);
    }
}

void outroState::initAudio(){
    m_soloud = new SoLoud::Soloud;
    m_soloud->init();

    m_sounds.insert({"aiEnd", SoLoud::Wav()});
    m_sounds.at("aiEnd").load("sounds/aiEnd.wav");
    m_sounds.at("aiEnd").set3dAttenuation(1,0.1);

    m_soloud->play(m_sounds.at("aiEnd"));

    m_sounds.insert({"ambient", SoLoud::Wav()});
    m_sounds.at("ambient").load("sounds/ambient.wav");
    m_sounds.at("ambient").setLooping(true);

    m_soloud->play(m_sounds.at("ambient"), 0.75);


}

void outroState::update3DAudio(){
    m_soloud->set3dListenerParameters(
        m_gameCam->m_position.x , m_gameCam->m_position.y, m_gameCam->m_position.z,
        m_gameCam->m_front.x, m_gameCam->m_front.y, m_gameCam->m_front.z,
        m_gameCam->m_up.x , m_gameCam->m_up.y , m_gameCam->m_up.z
    );
}

outroState::~outroState(){
    spdlog::info("Deleting playstate...");

    m_soloud->deinit();

    delete m_gameCam;
}

void outroState::initDeltaTime(){
    m_lastTime = glfwGetTime();   
}

void outroState::calculateDeltaTime(){
    float currTime = glfwGetTime();
    m_deltaTime = currTime - m_lastTime;
    m_lastTime = currTime;
}
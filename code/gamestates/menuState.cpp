#include <gamestates/menuState.hpp>
#include <spdlog/spdlog.h>

void menuState::init(GLFWwindow* referenceWindow){
    spdlog::info("Launching menu state...");

    m_window = referenceWindow;
    m_physics.init(m_window);
    m_physics.initDebugDrawer();

    initCameraPath();
    initGraphics();

    initPhysicsObjects();
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

    if(m_exit){
        glfwSetWindowShouldClose(m_window, true);
    }

}

bool menuState::shouldRun(){
    return !glfwWindowShouldClose(m_window);
}

nextStateEnum menuState::nextState(){
    if(m_play){
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
    m_graphics.loadShader("bulletDebug");

    m_frameBuffer = new FrameBuffer(windowWidth, windowHeight, windowWidth, windowHeight, m_graphics.getShader("framebuffer"));

    m_gameCam = new RailsCamera(m_window);
    m_gameCam->moveTo(m_cameraTargets.at(0).cameraPos, m_cameraTargets.at(0).cameraLookAt, 0);
    m_gameCam->m_moveSpeed = 5;

    assetLoader::loadAssetBundle(m_textures, m_models, "mainmenu");
}

void menuState::initCameraPath(){
    m_cameraTargets = loadCameraPath("assets/menu.path");
}

void menuState::initObjects(){
    spdlog::info("Initalizing Game Objects...");

    m_gameObjects.insert({"floor" , GameObject{m_models.at("floor")}});
    m_gameObjects.insert({"desk", GameObject{m_models.at("desk")}});
    m_gameObjects.insert({"wall", GameObject{m_models.at("wall")}});
    m_gameObjects.insert({"menubox", GameObject{m_models.at("menubox")}});
}

void menuState::initPhysicsObjects(){
    spdlog::info("Initalizing Physics colliders...");

    m_physics.createColObject("play");
    m_physics.addBoxCollider("play", reactphysics3d::Vector3(0.1 , 0.06 , 0.1), reactphysics3d::Vector3(5.4911, 6.182, 2.5));

    m_physics.createColObject("exit");
    m_physics.addBoxCollider("exit", reactphysics3d::Vector3(0.1 , 0.06, 0.1), reactphysics3d::Vector3(6.22, 6.182, 2.5));
}

void menuState::render(){
    if(m_renderAccumulator > m_renderTick){
        m_frameBuffer->Bind();
        m_graphics.renderStart();

        m_graphics.renderObjects(m_gameCam, m_textures, m_gameObjects);

        m_physics.debugRender(m_gameCam->m_view, m_gameCam->m_proj, m_graphics.getShader("bulletDebug"));
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

    m_input.registerKey("debugPlay", GLFW_KEY_KP_5, true);
}

void menuState::processInput(){
    if(m_input.isPressed("click")){
        Raycasthit playHit;
        playHit = m_physics.testMouseRayAgainstCollisionObject("play", m_gameCam->m_view, m_gameCam->m_proj, false);

        if(playHit.m_isHit){
            m_play = true;
        }

        Raycasthit exitHit;
        exitHit = m_physics.testMouseRayAgainstCollisionObject("exit", m_gameCam->m_view, m_gameCam->m_proj, false);

        if(exitHit.m_isHit){
            m_exit = true;
        }
    }
    if(m_input.isPressed("skipEsc") || m_input.isPressed("skipSpace")){
        if(m_currentCameraTarget >= (m_cameraTargets.size() - 1)){
            return;
        }

        m_currentCameraTarget++;
        cameraTargetObject target = m_cameraTargets.at(m_currentCameraTarget);
        m_gameCam->m_moveSpeed = target.movementSpeed;
        m_gameCam->moveTo(target.cameraPos, target.cameraLookAt, target.movementTime);
 
    }

    if(m_input.isPressed("debugPlay")){
        m_exit = true;
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

menuState::~menuState(){
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
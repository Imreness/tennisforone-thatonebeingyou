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
    initPhysicsObjects();
    initAudio();

    initInput();

    initDeltaTime();
}

void playState::initDeltaTime(){
    spdlog::info("Initalizing delta time...");
    m_lastTime = glfwGetTime();
}

void playState::initAudio(){
    m_soloud = new SoLoud::Soloud;
    m_soloud->init();

    //m_sounds.insert({"test", SoLoud::Wav()});

    //load ballbounces
    std::string path;
    std::string soundName;
    for(int i = 0; i < 21; i++){
        path = "sounds/bounce";path.append(std::to_string(i+1));path.append(".wav");
        soundName = "bounce"; soundName.append(std::to_string(i+1));

        m_sounds.insert({soundName, SoLoud::Wav()});
        m_sounds.at(soundName).load(path.c_str());
        m_sounds.at(soundName).set3dAttenuation(1, 0.15);
    }

    //m_sounds.at("test").load("sounds/dikk.wav");
}

void playState::calculateDeltaTime(){
    float currTime = glfwGetTime();
    m_deltaTime = currTime - m_lastTime;
    m_lastTime = currTime;
}

void playState::initGraphics(){
    spdlog::info("Initalizing graphics engine...");
    m_graphics.setTargetWindow(m_window);
    m_graphics.loadShader("debug");
    m_graphics.loadShader("bulletDebug");
    m_graphics.loadShader("ring");
    m_graphics.loadShader("light");

    glEnable(GL_DEPTH_TEST);

    m_debugCam = new DebugCamera(m_window);
    m_gameCam = new RailsCamera(m_window);
    m_gameCam->m_moveSpeed = 1;
    m_gameCam->moveTo(glm::vec3(-2.5, 0.8, 0), glm::vec3(0,1,0), 0);

    assetLoader::loadAssetBundle(m_textures, m_models, "gameplay");
}

void playState::initObjects(){
    spdlog::info("Initalizing Game Objects...");

    m_gameObjects.insert({"playerRacket" , GameObject{m_models.at("racket")}});
    m_gameObjects.insert({"enemyRacket" , GameObject{m_models.at("racket")}});
    m_gameObjects.insert({"shock", GameObject{m_models.at("shock")}});
    m_gameObjects.insert({"enemyShock", GameObject{m_models.at("shock")}});
    m_playerRacket = new playerRacket(m_gameObjects.at("playerRacket"), m_gameObjects.at("shock"));

    m_aiRacket = new aiRacket(m_gameObjects.at("enemyRacket"), m_gameObjects.at("enemyShock"), AIDIFFICULTY::MEDIUM);

    m_gameObjects.insert({"house", GameObject{m_models.at("house")}});
    m_gameObjects.insert({"cage", GameObject{m_models.at("cage")}});

    m_gameObjects.insert({"shadow", GameObject{m_models.at("Plane")}});
    m_gameObjects.at("shadow").m_render = false;
    m_gameObjects.insert({"ball", GameObject{m_models.at("ball")}});
    m_gameObjects.insert({"guidering", GameObject{m_models.at("guide")}});
    m_gameObjects.at("guidering").m_render = false;
    m_tennisBall = new tennisBall(m_gameObjects.at("ball"), m_gameObjects.at("shadow"), m_gameObjects.at("guidering"));

    m_tennisBall->m_minSpeed = 2;
    m_tennisBall->m_maxSpeed = 10;
    m_tennisBall->m_ballSpeedMultiplier = 1;

    m_tennisBall->resetBall(true);

    m_gameObjects.insert({"counterrack", GameObject{m_models.at("counterrack")}});

    m_gameObjects.insert({"nameplatePlayer", GameObject{m_models.at("nameplatePlayer")}});
    m_gameObjects.insert({"nameplateAI", GameObject{m_models.at("nameplateAI")}});

    //a level editor would come handy round this time :d
    m_gameObjects.insert({"playerLED1", GameObject{m_models.at("playerLED1")}});
    m_gameObjects.insert({"playerLED2", GameObject{m_models.at("playerLED2")}});
    m_gameObjects.insert({"playerLED3", GameObject{m_models.at("playerLED3")}});
    m_gameObjects.insert({"playerLED4", GameObject{m_models.at("playerLED4")}});
    m_gameObjects.insert({"playerLED5", GameObject{m_models.at("playerLED5")}});
    m_gameObjects.insert({"playerLED6", GameObject{m_models.at("playerLED6")}});

    m_gameObjects.at("playerLED1").m_render = false;
    m_gameObjects.at("playerLED2").m_render = false;
    m_gameObjects.at("playerLED3").m_render = false;
    m_gameObjects.at("playerLED4").m_render = false;
    m_gameObjects.at("playerLED5").m_render = false;
    m_gameObjects.at("playerLED6").m_render = false;

    m_gameObjects.insert({"aiLED1", GameObject{m_models.at("aiLED1")}});
    m_gameObjects.insert({"aiLED2", GameObject{m_models.at("aiLED2")}});
    m_gameObjects.insert({"aiLED3", GameObject{m_models.at("aiLED3")}});
    m_gameObjects.insert({"aiLED4", GameObject{m_models.at("aiLED4")}});
    m_gameObjects.insert({"aiLED5", GameObject{m_models.at("aiLED5")}});
    m_gameObjects.insert({"aiLED6", GameObject{m_models.at("aiLED6")}});

    m_gameObjects.at("aiLED1").m_render = false;
    m_gameObjects.at("aiLED2").m_render = false;
    m_gameObjects.at("aiLED3").m_render = false;
    m_gameObjects.at("aiLED4").m_render = false;
    m_gameObjects.at("aiLED5").m_render = false;
    m_gameObjects.at("aiLED6").m_render = false;

}

void playState::initPhysicsObjects(){
    spdlog::info("Initalizing Physics colliders...");

    m_physics.createColObject("racket");
    m_physics.addBoxCollider("racket", reactphysics3d::Vector3(0.12 , 0.15 , 0.15), reactphysics3d::Vector3(0.0, 0.0,0));

    m_physics.createColObject("enemyRacket");
    m_physics.addBoxCollider("enemyRacket", reactphysics3d::Vector3(0.05, 0.15, 0.15), reactphysics3d::Vector3(-0.1, 0 ,0));

    m_physics.createColObject("ball");
    m_physics.addSphereCollider("ball", 0.0438);

    m_physics.createColObject("backboard");
    m_physics.addBoxCollider("backboard", reactphysics3d::Vector3(0.05 , 1 , 2), reactphysics3d::Vector3(-.01 , 0.9, 0));

    m_physics.createColObject("enemybackboard");
    m_physics.addBoxCollider("enemybackboard", reactphysics3d::Vector3(0.05, 1, 2), reactphysics3d::Vector3(7, 0.9, 0));

    m_physics.createColObject("leftboard");
    m_physics.addBoxCollider("leftboard", reactphysics3d::Vector3(3.5, 1, 0.05 ), reactphysics3d::Vector3(3.5, 0.9, -2));

    m_physics.createColObject("rightboard");
    m_physics.addBoxCollider("rightboard", reactphysics3d::Vector3(3.5, 1, 0.05 ), reactphysics3d::Vector3(3.5, 0.9, 2));

    m_physics.createColObject("floorboard");
    m_physics.addBoxCollider("floorboard", reactphysics3d::Vector3(3.5 , 0.05, 2), reactphysics3d::Vector3(3.5, -.07,0));

    m_physics.createColObject("ceilingboard");
    m_physics.addBoxCollider("ceilingboard", reactphysics3d::Vector3(3.5 , 0.05, 2), reactphysics3d::Vector3(3.5, (2 - 0.07),0));

    m_physics.createColObject("mouseBoard");
    m_physics.addBoxCollider("mouseBoard", reactphysics3d::Vector3(0.0005, 50 , 50 ), reactphysics3d::Vector3(0, 0.9, 0));
}

void playState::render(){
    if(m_renderAccumulator > m_renderTick){
        m_graphics.renderStart();
    
        if(m_debugMode){
            m_graphics.renderObjects(m_debugCam, m_textures, m_gameObjects);
            m_graphics.renderObjects(m_debugCam, m_textures, m_gameObjects.at("shadow"));

            renderLights(true);
    
            m_physics.debugRender(m_debugCam->m_view, m_debugCam->m_proj, m_graphics.getShader("bulletDebug"));
        }
        else{
            m_graphics.renderObjects(m_gameCam, m_textures, m_gameObjects);
            m_graphics.renderObjects(m_gameCam, m_textures, m_gameObjects.at("shadow"));
            m_graphics.renderObjects(m_gameCam, m_textures, m_gameObjects.at("guidering"), "ring");

            renderLights(false);

            if(m_debugDrawingInGame){
                m_physics.debugRender(m_gameCam->m_view, m_gameCam->m_proj, m_graphics.getShader("bulletDebug"));
            }
        }
    
        m_graphics.renderEnd();
        m_renderAccumulator -= m_renderTick;
    }
    else{
        m_renderAccumulator += m_deltaTime;
    }
}

void playState::renderLights(bool isDebugCam){
    if(isDebugCam){
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("playerLED1"), m_score.isLEDLit(true,1));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("playerLED2"), m_score.isLEDLit(true,2));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("playerLED3"), m_score.isLEDLit(true,3));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("playerLED4"), m_score.isLEDLit(true,4));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("playerLED5"), m_score.isLEDLit(true,5));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("playerLED6"), m_score.isLEDLit(true,6));

        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("aiLED1"), m_score.isLEDLit(false,1));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("aiLED2"), m_score.isLEDLit(false,2));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("aiLED3"), m_score.isLEDLit(false,3));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("aiLED4"), m_score.isLEDLit(false,4));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("aiLED5"), m_score.isLEDLit(false,5));
        m_graphics.renderLight(m_debugCam, m_textures, m_gameObjects.at("aiLED6"), m_score.isLEDLit(false,6));
    }
    else{
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("playerLED1"), m_score.isLEDLit(true,1));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("playerLED2"), m_score.isLEDLit(true,2));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("playerLED3"), m_score.isLEDLit(true,3));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("playerLED4"), m_score.isLEDLit(true,4));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("playerLED5"), m_score.isLEDLit(true,5));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("playerLED6"), m_score.isLEDLit(true,6));
        
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("aiLED1"), m_score.isLEDLit(false,1));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("aiLED2"), m_score.isLEDLit(false,2));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("aiLED3"), m_score.isLEDLit(false,3));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("aiLED4"), m_score.isLEDLit(false,4));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("aiLED5"), m_score.isLEDLit(false,5));
        m_graphics.renderLight(m_gameCam, m_textures, m_gameObjects.at("aiLED6"), m_score.isLEDLit(false,6));
    }
}

void playState::process(){
    calculateDeltaTime();

    if(m_debugMode){
        m_debugCam->update(m_deltaTime);
    }
    else{
        m_gameCam->update(m_deltaTime);
    }

    processBall();
    processInput();
    processPlayerRacket();
    processAiRacket();
    update3DAudio();

    m_physics.update(m_deltaTime);

    render();
}

void playState::update3DAudio(){
    m_soloud->set3dListenerParameters(
        m_gameCam->m_position.x , m_gameCam->m_position.y, m_gameCam->m_position.z,
        m_gameCam->m_front.x, m_gameCam->m_front.y, m_gameCam->m_front.z,
        m_gameCam->m_up.x , m_gameCam->m_up.y , m_gameCam->m_up.z
    );
}

void playState::initInput(){
    spdlog::info("Initalizing Input...");
    m_input.init(m_window);

    glfwSetWindowUserPointer(m_window, this);

    m_input.registerKey("debugMode", GLFW_KEY_F1, true);
    m_input.registerKey("debugDrawingInGame", GLFW_KEY_F2, true);

    m_input.registerKey("debugResetBall", GLFW_KEY_KP_5, true);

    m_input.registerKey("debugTimehalf", GLFW_KEY_KP_7, true);
    m_input.registerKey("debugTimeNormal", GLFW_KEY_KP_8, true);
    m_input.registerKey("debugTimeonepointfive", GLFW_KEY_KP_9, true);

    m_input.registerKey("debugTestSound", GLFW_KEY_F3, true);
}

void playState::processInput(){

    if(m_input.isPressed("debugMode")){
        if(m_debugMode){
            m_debugMode = false;
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else{
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            m_debugMode = true;
        }
    }

    if(m_input.isPressed("debugDrawingInGame")){
        if(m_debugDrawingInGame){
            m_debugDrawingInGame = false;
        }
        else{
            m_debugDrawingInGame = true;
        }
    }

    if(m_input.isPressed("debugResetBall")){
        m_tennisBall->resetBall(true);
        m_score.reset();
        m_timeScale = 1;
    }

    if(m_input.isPressed("debugTestSound")){
        m_soloud->play(m_sounds.at("bounce17"));
    }

//    if(m_input.isPressed("debugTimehalf")){
//        m_timeScale = 0.5f;
//    }
//    else if(m_input.isPressed("debugTimeNormal")){
//        m_timeScale = 1.f;
//    }
//    else if(m_input.isPressed("debugTimeonepointfive")){
//        m_timeScale = 1.5f;
//    }
}

void playState::processPlayerRacket(){
    Raycasthit hit = m_physics.testMouseRayAgainstCollisionObject("mouseBoard", m_gameCam->m_view, m_gameCam->m_proj);
    if(hit.m_isHit){
        m_playerRacket->setTarget(hit.m_hitpos);
    }

    m_playerRacket->update(m_deltaTime * m_timeScale);

    m_physics.setTransformFromMat("racket", m_playerRacket->m_refObject.m_modelMat);
}

void playState::processAiRacket(){
    m_aiRacket->setTarget(glm::vec3(7, m_tennisBall->m_position.y, m_tennisBall->m_position.z));

    m_aiRacket->update(m_deltaTime * m_timeScale);

    m_physics.setTransformFromMat("enemyRacket", m_aiRacket->m_refObject.m_modelMat);
}

void playState::processBall(){
    Raycasthit shadowray = m_physics.testRayAgainstCollisionObject("floorboard", m_tennisBall->m_position, glm::vec3(0, -1, 0));
    float shadowdistance = glm::distance(shadowray.m_hitpos, m_tennisBall->m_position);
    m_tennisBall->calculateShadowScale(shadowdistance);


    Raycasthit guideray = m_physics.testRayAgainstCollisionObject("backboard", m_tennisBall->m_position, glm::vec3(-1, 0 ,0));
    m_tennisBall->calculateGuideRing(glm::distance(guideray.m_hitpos, m_tennisBall->m_position));

    m_tennisBall->update(m_deltaTime * m_timeScale);

    m_physics.setTransformFromMat("ball",m_tennisBall->m_refBall.m_modelMat);

    if(m_physics.testCollisionBodies("ball", "racket")){
        m_tennisBall->reflect(m_playerRacket->m_targetPosition - m_playerRacket->m_position);
        m_aiRacket->changeSpeed();

        //TODO - fix multiple plays
        m_soloud->play3d(m_sounds.at(getRandomBounceNoiseName()), m_tennisBall->m_position.x, m_tennisBall->m_position.y, m_tennisBall->m_position.z);
    }

    if(m_physics.testCollisionBodies("ball", "enemyRacket")){
        m_tennisBall->reflect(m_aiRacket->generateRackedDir(), true);
        m_soloud->play3d(m_sounds.at(getRandomBounceNoiseName()), m_tennisBall->m_position.x, m_tennisBall->m_position.y, m_tennisBall->m_position.z);
    }

    if(m_physics.testCollisionBodies("ball", "leftboard")){
        m_tennisBall->reflect(WallTypes::LEFT);
        m_soloud->play3d(m_sounds.at(getRandomBounceNoiseName()), m_tennisBall->m_position.x, m_tennisBall->m_position.y, m_tennisBall->m_position.z);
    }
    else if (m_physics.testCollisionBodies("ball", "rightboard")){
        m_tennisBall->reflect(WallTypes::RIGHT);
        m_soloud->play3d(m_sounds.at(getRandomBounceNoiseName()), m_tennisBall->m_position.x, m_tennisBall->m_position.y, m_tennisBall->m_position.z);
    }
    else if (m_physics.testCollisionBodies("ball", "floorboard")){
        m_tennisBall->reflect(WallTypes::FLOOR);
        m_soloud->play3d(m_sounds.at(getRandomBounceNoiseName()), m_tennisBall->m_position.x, m_tennisBall->m_position.y, m_tennisBall->m_position.z);
    }
    else if (m_physics.testCollisionBodies("ball", "ceilingboard")){
        m_tennisBall->reflect(WallTypes::TOP);
        m_soloud->play3d(m_sounds.at(getRandomBounceNoiseName()), m_tennisBall->m_position.x, m_tennisBall->m_position.y, m_tennisBall->m_position.z);
    }

    //debug shit pls delete before game is done much love homie :*
    else if(m_physics.testCollisionBodies("ball", "backboard")){
        m_score.addPoints(false);

        if(m_score.m_aiScore == m_score.m_maxScore){
            m_timeScale = 0;
        }

        m_tennisBall->resetBall(false);
    }
    else if(m_physics.testCollisionBodies("ball", "enemybackboard")){
        m_score.addPoints(true);

        if(m_score.m_playerScore == m_score.m_maxScore){
            m_timeScale = 0;
        }

        m_tennisBall->resetBall(true);
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
    spdlog::info("Deleting playstate...");

    m_soloud->deinit();

    delete m_debugCam;
    delete m_playerRacket;
    delete m_tennisBall;
    delete m_gameCam;
}

std::string playState::getRandomBounceNoiseName(){
    std::string baseString = "bounce";

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> numberRange(1, 21);

    int randomnumber = numberRange(mt);
    baseString.append(std::to_string(randomnumber));
    return baseString;
}
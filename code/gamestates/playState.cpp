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

    initInput();

    initDeltaTime();
}

void playState::initDeltaTime(){
    m_lastTime = glfwGetTime();
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
    m_gameCam->moveTo(glm::vec3(-2.4, 0.8, 0), glm::vec3(0,0.9,0), 0);

    assetLoader::loadAssetBundle(m_textures, m_models, "gameplay");
}

void playState::initObjects(){
    m_gameObjects.insert({"playerRacket" , GameObject{m_models.at("racket")}});
    m_gameObjects.insert({"shock", GameObject{m_models.at("shock")}});
    m_playerRacket = new playerRacket(m_gameObjects.at("playerRacket"), m_gameObjects.at("shock"));

    m_gameObjects.insert({"house", GameObject{m_models.at("house")}});
    m_gameObjects.insert({"cage", GameObject{m_models.at("cage")}});

    m_gameObjects.insert({"shadow", GameObject{m_models.at("Plane")}});
    m_gameObjects.insert({"ball", GameObject{m_models.at("ball")}});
    m_tennisBall = new tennisBall(m_gameObjects.at("ball"), m_gameObjects.at("shadow"));
    m_tennisBall->resetBall(true);

}

void playState::initPhysicsObjects(){
    m_physics.createColObject("racket");
    m_physics.addBoxCollider("racket", reactphysics3d::Vector3(0.05 , 0.15 , 0.15), reactphysics3d::Vector3(0.0, 0.0,0));

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
    
            m_physics.debugRender(m_debugCam->m_view, m_debugCam->m_proj, m_graphics.getShader("bulletDebug"));
        }
        else{
            m_graphics.renderObjects(m_gameCam, m_textures, m_gameObjects);
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

    m_physics.update(m_deltaTime);

    render();
}

void playState::initInput(){
    m_input.init(m_window);

    glfwSetWindowUserPointer(m_window, this);

    m_input.registerKey("debugMode", GLFW_KEY_F1, true);
    m_input.registerKey("debugDrawingInGame", GLFW_KEY_F2, true);

    m_input.registerKey("rotateleft"    , GLFW_KEY_A, true);
    m_input.registerKey("rotateright"   , GLFW_KEY_D, true);

    m_input.registerKey("debugResetBall", GLFW_KEY_KP_5, true);
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

    if(m_input.isPressed("rotateleft")){
        m_playerRacket->rotate(RACKETMOVEMENT::LEFT,m_deltaTime);
    }
    else if(m_input.isPressed("rotateright")){
        m_playerRacket->rotate(RACKETMOVEMENT::RIGHT,m_deltaTime);
    }

    if(m_input.isPressed("debugResetBall")){
        m_tennisBall->resetBall(true);
    }
}

void playState::processPlayerRacket(){
    Raycasthit hit = m_physics.testMouseRayAgainstCollisionObject("mouseBoard", m_gameCam->m_view, m_gameCam->m_proj);
    if(hit.m_isHit){
        m_playerRacket->setTarget(hit.m_hitpos);
    }

    m_playerRacket->update(m_deltaTime);

    m_physics.setTransformFromMat("racket", m_playerRacket->m_refObject.m_modelMat);
}

void playState::processBall(){
    Raycasthit shadowray = m_physics.testRayAgainstCollisionObject("floorboard", m_tennisBall->m_position, glm::vec3(0, -1, 0));

    float shadowdistance = glm::distance(shadowray.m_hitpos, m_tennisBall->m_position);
    
    m_tennisBall->calculateShadowScale(shadowdistance);
    m_tennisBall->update(m_deltaTime);

    m_physics.setTransformFromMat("ball",m_tennisBall->m_refBall.m_modelMat);

    if(m_physics.testCollisionBodies("ball", "racket")){
        glm::vec3 center = glm::vec3(m_physics.getColObject("racket")->m_col->getLocalToWorldTransform().getPosition().x,  m_physics.getColObject("racket")->m_col->getLocalToWorldTransform().getPosition().y,  m_physics.getColObject("racket")->m_col->getLocalToWorldTransform().getPosition().z);
        m_tennisBall->reflect(1, m_tennisBall->m_position, center);
    }

    if(m_physics.testCollisionBodies("ball", "leftboard")){
        m_tennisBall->reflect(WallTypes::LEFT);
    }
    else if (m_physics.testCollisionBodies("ball", "rightboard")){
        m_tennisBall->reflect(WallTypes::RIGHT);
    }
    else if (m_physics.testCollisionBodies("ball", "floorboard")){
        m_tennisBall->reflect(WallTypes::FLOOR);
    }
    else if (m_physics.testCollisionBodies("ball", "ceilingboard")){
        m_tennisBall->reflect(WallTypes::TOP);
    }

    //debug shit pls delete before game is done much love homie :*
    else if(m_physics.testCollisionBodies("ball", "backboard")){
        //m_tennisBall->reflect(WallTypes::PLAYER);
    }
    else if(m_physics.testCollisionBodies("ball", "enemybackboard")){
        m_tennisBall->reflect(WallTypes::ENEMY);
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
   delete m_tennisBall;
   delete m_gameCam;
}
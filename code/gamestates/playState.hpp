#ifndef PLAYSTATE
#define PLAYSTATE
#include <core/gamestate.hpp>
#include <core/assetLoader.hpp>
#include <core/graphicsEngine.hpp>
#include <core/inputManager.hpp>
#include <core/physicsEngine.hpp>

#include <objects/gameObject.hpp>

#include <objects/playerRacket.hpp>
#include <objects/aiRacket.hpp>
#include <objects/tennisBall.hpp>

class playState : public gameState{
private:
    graphicsEngine m_graphics;
    InputManager m_input;
    PhysicsEngine m_physics;


    std::vector<Texture*> m_textures;
    std::unordered_map<std::string, Model*> m_models;

    std::unordered_map<std::string, GameObject> m_gameObjects;

    DebugCamera* m_debugCam;
    RailsCamera* m_gameCam;

    playerRacket* m_playerRacket;
    aiRacket* m_aiRacket;
    tennisBall* m_tennisBall;

    bool m_debugMode = false;
    bool m_debugDrawingInGame = false;

    float m_renderAccumulator = 0;
    float m_renderTick = 1. / 60.;

    //Time
    float m_lastTime;
    float m_deltaTime;

    float m_timeScale = 1.f;

    //rendering
    void initGraphics();
    void initObjects();

    void render();
    void renderLights(bool isDebugCam);

    void initInput();
    void processInput();

    void initPhysicsObjects();

    void processPlayerRacket();
    void processAiRacket();
    void processBall();

    void initDeltaTime();
    void calculateDeltaTime();

public:

    virtual void init(GLFWwindow*);

    virtual void process();

    virtual bool shouldRun();

    virtual nextStateEnum nextState();

    virtual ~playState();

};

#endif
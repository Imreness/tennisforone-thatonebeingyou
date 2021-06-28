#ifndef PLAYSTATE
#define PLAYSTATE
#include <core/gamestate.hpp>
#include <core/assetLoader.hpp>
#include <core/graphicsEngine.hpp>
#include <core/inputManager.hpp>
#include <core/physicsEngine.hpp>

#include <objects/gameObject.hpp>

#include <objects/playerRacket.hpp>

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

    bool m_debugMode = false;
    bool m_debugDrawingInGame = false;

    //deltaTime
    float m_lastTime;
    float m_deltaTime;

    //rendering
    void initGraphics();
    void initObjects();
    void render();

    void initInput();
    void processInput();

    void processPlayerRacket();

    void calculateDeltaTime();

public:

    virtual void init(GLFWwindow*);

    virtual void process();

    virtual bool shouldRun();

    virtual nextStateEnum nextState();

    virtual ~playState();

};

#endif
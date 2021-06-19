#ifndef PLAYSTATE
#define PLAYSTATE
#include <core/gamestate.hpp>
#include <core/assetLoader.hpp>
#include <core/graphicsEngine.hpp>

#include <objects/gameObject.hpp>

class playState : public gameState{
private:
    graphicsEngine m_graphics;

    std::vector<Texture*> m_textures;
    std::unordered_map<std::string, Model*> m_models;

    std::vector<GameObject> m_gameObjects;


    DebugCamera* m_debugCam;
    RailsCamera* m_gameCam;

    bool m_debugMode = false;
    bool m_debugModeJustSwitched = false;

    //deltaTime
    float m_lastTime;
    float m_deltaTime;

    //rendering
    void initGraphics();
    void initObjects();
    void render();

    void processInput();

    void calculateDeltaTime();

public:

    virtual void init(GLFWwindow*);

    virtual void process();

    virtual bool shouldRun();

    virtual nextStateEnum nextState();

    virtual ~playState();

};

#endif
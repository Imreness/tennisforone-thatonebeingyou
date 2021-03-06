#ifndef MENUSTATE
#define MENUSTATE
#include <core/gamestate.hpp>
#include <core/assetLoader.hpp>
#include <core/graphicsEngine.hpp>
#include <core/physicsEngine.hpp>

#include <core/inputManager.hpp>
#include <core/framebuffer.hpp>

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

class menuState : public gameState{
private:
    graphicsEngine m_graphics;
    InputManager   m_input;
    FrameBuffer*   m_frameBuffer;
    PhysicsEngine  m_physics;

    float m_brightness = 0.0000000001f;
    //if its false, we're fading in
    bool m_fadeOut = false;
    float m_fadeSpeed = 3.f;

    std::vector<Texture*> m_textures;
    std::unordered_map<std::string, Model*>     m_models;
    std::unordered_map<std::string, GameObject> m_gameObjects;

    RailsCamera* m_gameCam;

    bool m_exit = false;
    bool m_play = false;

    SoLoud::Soloud* m_soloud;
    std::unordered_map<std::string, SoLoud::Wav> m_sounds;

    float m_renderAccumulator = 0;
    float m_renderTick        = 1. / 60.;

    float m_lastTime;
    float m_deltaTime;

    void initGraphics();
    void initObjects();
    void initPhysicsObjects();

    void render();
    void processFading();

    void initInput();
    void processInput();

    std::vector<cameraTargetObject> m_cameraTargets;
    int m_currentCameraTarget = 0;
    void initCameraPath();

    void initDeltaTime();
    void calculateDeltaTime();

    void initAudio();
    void update3DAudio();


public:
    virtual void init(GLFWwindow*);

    virtual void process();

    virtual bool shouldRun();

    virtual nextStateEnum nextState();

    virtual ~menuState();

};

#endif
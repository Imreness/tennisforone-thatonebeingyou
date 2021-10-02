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

#include <objects/scoreKeeper.hpp>

#include <core/framebuffer.hpp>


#define WITH_ALSA
#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

class playState : public gameState{
private:
    bool m_exit = false;

    graphicsEngine m_graphics;
    InputManager m_input;
    PhysicsEngine m_physics;
    FrameBuffer* m_frameBuffer;

    float m_brightness = 0.0000000001f;
    //if its false, we're fading in
    bool m_fadeOut = false;
    float m_fadeSpeed = 3.f;


    std::vector<Texture*> m_textures;
    std::unordered_map<std::string, Model*> m_models;

    std::unordered_map<std::string, GameObject> m_gameObjects;

    ScoreKeeper m_score;
    int m_maxDifficulty = 0;

    DebugCamera* m_debugCam;
    RailsCamera* m_gameCam;

    playerRacket* m_playerRacket;
    aiRacket* m_aiRacket;
    tennisBall* m_tennisBall;

    SoLoud::Soloud* m_soloud;
    std::unordered_map<std::string, SoLoud::Wav> m_sounds;

    bool m_debugMode = false;
    bool m_debugDrawingInGame = false;

    float m_renderAccumulator = 0;
    float m_renderTick = 1. / 60.;

    //Time
    float m_lastTime;
    float m_deltaTime;

    float m_currTimeScale = 1.f;

    //rendering
    void initGraphics();
    void initObjects();

    void render();
    //Lights as in LED lights. Not LIGHT lights :P
    void renderLights(bool isDebugCam);
    void processFading();

    void initInput();
    void processInput();
    void process3DButtons();

    void initPhysicsObjects();

    void processPlayerRacket();
    void processAiRacket();
    void processBall();
    void processBulletTime();

    void initDeltaTime();
    void calculateDeltaTime();

    void initAudio();
    void update3DAudio();

    void changeAIDifficulty(bool increase);

    //shouldve made a seperate "AudioManager" class or sumthang like that, cuz 
    std::string getRandomBounceNoiseName();

public:

    virtual void init(GLFWwindow*);

    virtual void process();

    virtual bool shouldRun();

    virtual nextStateEnum nextState();

    virtual ~playState();

};

#endif
#include <core/game.hpp>
#include <iostream>
#include <fstream>

void Game::initspdlog(){
    m_currConfig = config::loadConfig("game.conf");


    //setup logging
	auto logfile = spdlog::basic_logger_mt("log", "game.log");

	spdlog::set_default_logger(logfile);
	spdlog::set_level(m_currConfig.debuglevel);
    spdlog::flush_on(spdlog::level::level_enum::err);
	spdlog::flush_every(std::chrono::seconds(1));

	spdlog::debug("Started game constructor");

	std::ofstream ofs;
	ofs.open("game.log", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

}

void Game::initGLFW(const char* title){
    spdlog::debug("Initalizing GLFW");
    //Init GLFW and the window itself
    if(!glfwInit()){
        spdlog::error("Error initalizing GLFW!");
        abort();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    //OpenGL profile should be CORE profile, instead of compat profile. But, this makes it work on Nvidia GPus under linux,
    //plus, it doesnt seem to break anything under AMD/Intel offerings.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    //Init window here
    if(m_currConfig.fullscreen){
        m_mainWindow = glfwCreateWindow(m_currConfig.windowWidth, m_currConfig.windowHeight, title, glfwGetPrimaryMonitor(), NULL);
    }
    else{
        m_mainWindow = glfwCreateWindow(m_currConfig.windowWidth, m_currConfig.windowHeight, title, NULL, NULL);
    }
    if(!m_mainWindow){
        glfwTerminate();
        spdlog::error("Error while creating the game window!");
        abort();
    }
    glfwMakeContextCurrent(m_mainWindow);
}

void Game::initOpenGL(){
    //Init OpenGL
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        spdlog::error("Error initalizing OpenGL!");
        abort();
    }

    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0,0,m_currConfig.windowWidth,m_currConfig.windowHeight);
}

Game::Game(const char* windowtitle){

    initspdlog();

    spdlog::info("Initalizing graphics...");    

    initGLFW(windowtitle);
    initOpenGL();

    //Init the first game state
    spdlog::info("Initilizing game...");
    
    m_currState = new menuState();
    m_currState->init(m_mainWindow);

    
    spdlog::info("Running game yay!");
}

void Game::update(){

    m_currState->process();
    m_shouldRun = m_currState->shouldRun();

    nextStateEnum nextState = m_currState->nextState();
    if(nextState != nextStateEnum::NOTHING){
        switchState(nextState);
    }

}

bool Game::shouldRun(){
    return m_shouldRun;
}

Game::~Game(){
    delete m_currState;
    glfwTerminate();
}

void Game::switchState(nextStateEnum state){

    spdlog::debug("switching states...");

    //I obviously need a way to signal the main game class "AYO WEE NED A SWITCH"
    //and obviously, a messaging system would be best... although technically this is a messaging system.
    //A system that works well and fast. No reason to have a comment  here, I just think there should be better way of signaling state-switching
    //apart from "yo return this pls"
    switch (state){
        case nextStateEnum::GAME:
            delete m_currState;
            m_currState = new playState();
            m_currState->init(m_mainWindow);
            break;
        
        case nextStateEnum::MENU:
            delete m_currState;
            m_currState = new menuState();
            m_currState->init(m_mainWindow);

            break;

        case nextStateEnum::INTRO:
            delete m_currState;
            m_currState = new introState();
            m_currState->init(m_mainWindow);
            break;

        case nextStateEnum::OUTRO:
            delete m_currState;
            m_currState = new outroState();
            m_currState->init(m_mainWindow);
    }
}
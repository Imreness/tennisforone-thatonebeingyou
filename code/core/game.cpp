#include <core/game.hpp>
#include <iostream>
#include <fstream>

void Game::initspdlog(){
    m_currConfig = config::loadConfig("game.conf");

	auto logfile = spdlog::basic_logger_mt("log", "game.log");

	spdlog::set_default_logger(logfile);
	spdlog::set_level(m_currConfig.debuglevel);

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
        std::this_thread::sleep_for(std::chrono::seconds(1));
        abort();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    //Init window here
    m_mainWindow = glfwCreateWindow(m_currConfig.windowWidth, m_currConfig.windowHeight, title, NULL, NULL);
    if(!m_mainWindow){
        glfwTerminate();
        spdlog::error("Error while creating the game window!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        abort();
    }
    glfwMakeContextCurrent(m_mainWindow);
}

void Game::initOpenGL(){
    //Init OpenGL
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        spdlog::error("Error initalizing OpenGL!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        abort();
    }

    //backside of polygons wont be rendered. quite useful optimization.
    glEnable(GL_CULL_FACE);
    glViewport(0,0,m_currConfig.windowWidth,m_currConfig.windowHeight);
}

Game::Game(const char* windowtitle){

    initspdlog();

    initGLFW(windowtitle);

    initOpenGL();

    //Init the first game state
    spdlog::info("Initilizing game...");
    
    m_currState = new menuState();
    m_currState->init(m_mainWindow);

    
    spdlog::info("Running game");
}

void Game::update(){

    m_currState->process();

    m_shouldRun = m_currState->shouldRun();

}

bool Game::shouldRun(){
    return m_shouldRun; 
}

Game::~Game(){
    m_currState->cleanup();
    delete m_currState;
    glfwTerminate();
}
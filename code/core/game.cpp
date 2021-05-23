#include <core/game.hpp>
#include <iostream>
#include <fstream>

void Game::initspdlog(){
    m_currConfig = config::loadConfig("game.conf");

	auto logfile = spdlog::basic_logger_mt("log", "gamelog.log");

	spdlog::set_default_logger(logfile);
	spdlog::set_level(m_currConfig.debuglevel);

	spdlog::flush_every(std::chrono::seconds(1));

	spdlog::debug("Started game constructor");

	std::ofstream ofs;
	ofs.open("gamelog.log", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

}

void Game::initGLFW(const char* title){
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
}

Game::Game(const char* windowtitle){

    initspdlog();

    initGLFW(windowtitle);

    initOpenGL();

    //Init the first game state
    spdlog::info("Initilizing game...");

}

void Game::update(){
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.1, 0.1 ,0.1 , 1.);

    /* Swap front and back buffers */
    glfwSwapBuffers(m_mainWindow);

    /* Poll for and process events */
    glfwPollEvents();

    m_shouldRun = !glfwWindowShouldClose(m_mainWindow);

}

bool Game::shouldRun(){
    return m_shouldRun; 
}

Game::~Game(){
    std::printf("CALLED\n");
    //deconstruct the current gamestate
    glfwTerminate();
}
#include <core/game.hpp>
#include <core/configloader.hpp>
#include <iostream>
#include <fstream>

Game::Game(const char* title){
    //init config
    configStruct currconfig = config::loadConfig("game.conf");

    //setup logger
	auto logfile = spdlog::basic_logger_mt("log", "gamelog.log");

	spdlog::set_default_logger(logfile);
	spdlog::set_level(currconfig.debuglevel);

	spdlog::flush_every(std::chrono::seconds(1));

	spdlog::debug("Started game constructor");

	std::ofstream ofs;
	ofs.open("gamelog.log", std::ofstream::out | std::ofstream::trunc);
	ofs.close();


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
    m_mainWindow = glfwCreateWindow(currconfig.windowWidth, currconfig.windowHeight, title, NULL, NULL);
    if(!m_mainWindow){
        glfwTerminate();
        spdlog::error("Error while creating the game window!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        abort();
    }
    glfwMakeContextCurrent(m_mainWindow);






    //Init OpenGL
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        spdlog::error("Error initalizing OpenGL!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        abort();
    }

    //backside of polygons wont be rendered. quite useful optimization.
    glEnable(GL_CULL_FACE);

    //Init the first game state

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
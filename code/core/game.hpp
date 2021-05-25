#ifndef GAMECLASS
#define GAMECLASS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <core/configloader.hpp>
#include <gamestates/menuState.hpp>

class Game{
private:

    configStruct m_currConfig;

    GLFWwindow* m_mainWindow;

    bool m_shouldRun = true;

    gameState* m_currState;



    //init functions
    void initspdlog();
    void initGLFW(const char*);
    void initOpenGL();


public:

    //make debug level config defined
    Game(const char*);

    void update();

    bool shouldRun();
    
    ~Game();

};

#endif
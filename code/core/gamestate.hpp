#ifndef GAMESTATEBASECLASS
#define GAMESTATEBASECLASS
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <objects/cameraPathLoader.hpp>

enum class nextStateEnum{
    NOTHING,
    GAME,
    MENU,
    INTRO,
    OUTRO
};

//Base class for other states to build upon
class gameState{
protected:

    GLFWwindow* m_window;

public:

    virtual void init(GLFWwindow*) = 0;

    virtual void process() = 0;

    virtual bool shouldRun() = 0;

    virtual nextStateEnum nextState() = 0;

    virtual ~gameState(){}

};

#endif
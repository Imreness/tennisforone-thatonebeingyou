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

//Side note:
//This base class is a LOT MORE bare bones than it actually needs to be. Universtal stuff like input handling and rendering
//SHOULD be handeled in the base class as well, to reduce clutter in the states. Power of hindsight i guess

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
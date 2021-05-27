#ifndef GAMESTATEBASECLASS
#define GAMESTATEBASECLASS
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class gameState{
protected:

    GLFWwindow* m_window;

public:

    virtual void init(GLFWwindow*) = 0;

    virtual void process() = 0;

    virtual void cleanup() = 0;

    virtual bool shouldRun() = 0;

};

#endif
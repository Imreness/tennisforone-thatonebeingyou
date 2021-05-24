#include <core/gamestate.hpp>

class menuState : public gameState{
private:

public:
    virtual void init(GLFWwindow*);

    virtual void process();

    virtual void cleanup();

    virtual bool shouldRun();

};
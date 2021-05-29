#ifndef MENUSTATE
#define MENUSTATE
#include <core/gamestate.hpp>
#include <core/assetLoader.hpp>
#include <core/graphicsEngine.hpp>

class menuState : public gameState{
private:
    uiManager m_uiManager;
    graphicsEngine m_graphics;

    void initGraphics();
    void initUI();


    //rendering
    void render();

public:
    virtual void init(GLFWwindow*);

    virtual void process();

    virtual void cleanup();

    virtual bool shouldRun();

};

#endif
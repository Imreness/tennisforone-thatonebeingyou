#ifndef MENUSTATE
#define MENUSTATE
#include <core/gamestate.hpp>
#include <core/assetLoader.hpp>
#include <core/graphicsEngine.hpp>

class menuState : public gameState{
private:
    uiManager m_uiManager;
    graphicsEngine m_graphics;

    //ui
    void initUI();
    void processUIClick();

    //rendering
    void initGraphics();
    void render();

public:
    virtual void init(GLFWwindow*);

    virtual void process();

    virtual bool shouldRun();

    virtual ~menuState();

};

#endif
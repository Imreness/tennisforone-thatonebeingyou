#ifndef PLAYSTATE
#define PLAYSTATE
#include <core/gamestate.hpp>
#include <core/assetLoader.hpp>
#include <core/graphicsEngine.hpp>

class playState : public gameState{
private:
    graphicsEngine m_graphics;

    std::vector<Texture*> m_textures;
    std::unordered_map<std::string, Model*> m_models;

    //rendering
    void initGraphics();
    void render();

public:
    virtual void init(GLFWwindow*);

    virtual void process();

    virtual bool shouldRun();

    virtual nextStateEnum nextState();

    virtual ~playState();

};

#endif
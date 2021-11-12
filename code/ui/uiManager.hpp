#ifndef UIMANAGER
#define UIMANAGER
#include <core/texture.hpp>
#include <ui/uiTypes.hpp>
#include <unordered_map>
#include <string>

//Side note:
//My take on an aspect-ratio independent UI system. It doesnt work at all.(Well it works to SOME extent...) And it isn't used at all!
//I wrote this without any external material which was a really dumb thing to do, I really should've read some UI material before hand.
//In the end, since I prefer in-game UI (Things like the 007 Golden eye wrist watch, the PipBoy and the lockpicking minigame in TES V)
//i ended up implementing a proper 3D button system, so i circumvented this entire part of the code.
//I should read some materials about this topic...

class uiManager{
public:
    std::unordered_map<std::string, Texture*> m_textures;

    std::string m_hovered_button;
    std::unordered_map<std::string, uiButton> m_buttons;

    std::unordered_map<std::string, uiPanel> m_panels;

    int m_screenWidth = 0;
    int m_screenHeight = 0;

    void update(int , int);

    void setup(std::string);

    ~uiManager();

};

#endif
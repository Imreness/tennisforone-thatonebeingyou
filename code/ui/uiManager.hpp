#ifndef UIMANAGER
#define UIMANAGER
#include <core/texture.hpp>
#include <ui/uiTypes.hpp>
#include <unordered_map>
#include <string>

class uiManager{
public:
    std::unordered_map<std::string, Texture> m_textures;

    std::string m_hovered_button;
    std::unordered_map<std::string, uiButton> m_buttons;

    int m_screenWidth = 0;
    int m_screenHeight = 0;

    void update(int , int);

    void setup(std::string);

};

#endif
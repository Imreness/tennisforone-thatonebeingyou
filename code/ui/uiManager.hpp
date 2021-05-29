#ifndef UIMANAGER
#define UIMANAGER
#include <core/texture.hpp>
#include <unordered_map>
#include <string>


class uiManager{
public:
    std::unordered_map<std::string, Texture> m_textures;

};

#endif
#ifndef ASSETLOADER
#define ASSETLOADER

#include <unordered_map>
#include <core/texture.hpp>
#include <string>

namespace assetLoader{

    void loadUiPackage(std::unordered_map<std::string, Texture*>& ,const char*);

}

#endif
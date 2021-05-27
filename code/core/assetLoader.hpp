#ifndef ASSETLOADER
#define ASSETLOADER

#include <unordered_map>
#include <core/texture.hpp>
#include <string>

namespace assetLoader{

    std::unordered_map<std::string, Texture> loadUiPackage(const char*);

}

#endif
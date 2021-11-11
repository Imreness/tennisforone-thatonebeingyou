#ifndef ASSETLOADER
#define ASSETLOADER

#include <unordered_map>
#include <core/texture.hpp>
#include <core/model.hpp>
#include <string>

namespace assetLoader{

    void loadUiPackage(std::unordered_map<std::string, Texture*>& ,const char*);

    void loadAssetBundle(std::vector<Texture*>&, std::unordered_map<std::string, Model*>&, const char*);

}

#endif
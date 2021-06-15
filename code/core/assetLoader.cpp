#include <core/assetLoader.hpp>
#include <fstream>
#include <core/binaryfile.hpp>

void assetLoader::loadUiPackage(std::unordered_map<std::string, Texture*>& textures,const char* path){

    std::string fullpath("assets/"); fullpath.append(path); fullpath.append(".ui");

    binaryFile file;
    file.open(fullpath.c_str(), false);

    uint8_t textureAmount = file.read<uint8_t>();

    for(int i = 0; i < textureAmount; i++){
        char* nameChar = file.readChars(15);
        std::string name(nameChar);
        delete[] nameChar;

        uint16_t textureWidth = file.read<uint16_t>();
        uint16_t textureHeight = file.read<uint16_t>();

        char* data = file.readChars(textureWidth*textureHeight*4);

        textures.insert({name , new Texture(textureWidth,textureHeight,data,0)});
    }

    file.close();
}
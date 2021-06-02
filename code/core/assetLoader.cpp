#include <core/assetLoader.hpp>
#include <fstream>

void assetLoader::loadUiPackage(std::unordered_map<std::string, Texture*>& textures,const char* path){

    std::string fullpath("assets/"); fullpath.append(path); fullpath.append(".ui");

    std::ifstream file;
	file.open(fullpath.c_str(), std::ios::in | std::ios::binary);

    uint8_t textureAmount = 0;
    char* textureAmountChar = new char[sizeof(uint8_t)];
    file.read(textureAmountChar, sizeof(uint8_t));
    textureAmount = *(char*)textureAmountChar;
    delete[] textureAmountChar;

    for(int i = 0; i < textureAmount; i++){
        char* nameChar = new char[sizeof(char)*15];
        file.read(nameChar, sizeof(char)*15);
        std::string name(nameChar);
        delete[] nameChar;

        uint16_t textureWidth = 0;
        uint16_t textureHeight = 0;
        char* textureWidthChar = new char[sizeof(uint16_t)];
        char* textureHeightChar = new char[sizeof(uint16_t)];
        file.read(textureWidthChar, sizeof(uint16_t));
        file.read(textureHeightChar, sizeof(uint16_t));
        textureWidth = *(uint16_t*)textureWidthChar;
        textureHeight = *(uint16_t*)textureHeightChar;
        delete[] textureHeightChar;
        delete[] textureWidthChar;

        char* data = new char[textureWidth*textureHeight*4];
        file.read(data, textureWidth*textureHeight*4);

        textures.insert({name , new Texture(textureWidth,textureHeight,data,0)});
    }
}
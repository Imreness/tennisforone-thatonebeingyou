#include <core/assetLoader.hpp>
#include <fstream>

std::unordered_map<std::string, Texture> loadUiPackage(const char* path){
    std::unordered_map<std::string, Texture> textures;

    std::string fullpath("assets/"); fullpath.append(path);

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
        char* textureWidthChar;
        char* textureHeightChar;
        file.read(textureWidthChar, sizeof(uint16_t)); file.read(textureHeightChar, sizeof(uint16_t));
        textureWidth = *(uint16_t*)textureWidthChar; textureHeight = *(uint16_t*)textureHeightChar;
        delete[] textureHeightChar;
        delete[] textureWidthChar;

        char* data = new char[textureWidth*textureHeight*4];
        file.read(data, textureWidth*textureHeight*4);

        textures.insert({name , Texture(textureWidth,textureHeight,data,0)});
    }

    return textures;

}
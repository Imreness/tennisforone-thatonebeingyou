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

void assetLoader::loadAssetBundle(std::vector<Texture*>& textures,
    std::unordered_map<std::string, Model*>& models,
    const char* path){

    std::string fullpath("assets/"); fullpath.append(path); fullpath.append(".assetbundle");

    binaryFile file;
    file.open(fullpath.c_str(), false);

    int textureAmount = file.read<uint8_t>();
    int modelAmount = file.read<uint8_t>();

    for(int i = 0; i < textureAmount; i++){
        int textureWidth = file.read<uint16_t>();
        int textureHeight = file.read<uint16_t>();

        char* data = file.readChars(textureWidth*textureHeight*4);

        textures.push_back(new Texture(textureWidth, textureHeight, data, 0));
    }

    for(int i = 0; i < modelAmount; i++){
        char* name = file.readChars(25);
        std::string nameString(name); delete[] name;

        unsigned int textureID = file.read<uint8_t>();

        VertexData vertDat;

        int verticesAmount = file.read<uint32_t>();
        for(int x = 0; x < verticesAmount; x++){
            //Vertex coords
            vertDat.vertices.push_back(file.read<float_t>());
            vertDat.vertices.push_back(file.read<float_t>());
            vertDat.vertices.push_back(file.read<float_t>());

            //Texture coords
            vertDat.vertices.push_back(file.read<float_t>());
            vertDat.vertices.push_back(file.read<float_t>());
        }

        int indiciesAmount = file.read<uint32_t>();
        for(int x = 0; x < indiciesAmount; x++){
            vertDat.indicies.push_back(file.read<uint32_t>());
            vertDat.indicies.push_back(file.read<uint32_t>());
            vertDat.indicies.push_back(file.read<uint32_t>());
        }

        models.insert({nameString, new Model(vertDat)});
    }
}
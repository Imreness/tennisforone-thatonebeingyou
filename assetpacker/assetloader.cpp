#include <uiloader.cpp>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/*
    .assetbundle files
    
    8bit int - amount of textures
    8bit int - amount of models

    per texture:
    16bit int - width
    16bit int - height
    width*height*4*8bit - data

    per model:
    8bit int - textureID
    32bit int - verticesamount
    Xbit - vertices
    32bit int - indicies amount
    Xbit - indicies


*/

namespace assetloader{
    uint8_t textureAmount = 0;
    uint8_t modelAmount = 0;

    void packmodel(const char* modelpath, std::ofstream& file);

    void pack(){
        std::printf("Name a subfolder\n");
        std::string subfolder;
        std::getline(std::cin, subfolder);

        std::string path("assets/");
        path.append(subfolder);

        std::string outfilePath("../assets/");
        outfilePath.append(subfolder.c_str()).append(".assetbundle");

        std::ofstream outfile;
        outfile.open(outfilePath.c_str(), std::ios::out | std::ios::binary);

        const char* placeholder = new char[1];
        //place reserved for texture amount
        outfile.write(placeholder, sizeof(char));
        //place reserved for model amount
        outfile.write(placeholder, sizeof(char));


        textureAmount = 0;
        modelAmount = 0;

        while(true){
            std::printf("Name a file to pack\n");
             
            std::string assetfileName;
            std::getline(std::cin, assetfileName);
            std::string modelpath("assets/");
            modelpath.append(subfolder.c_str()).append("/").append(assetfileName);
            packmodel(modelpath.c_str(), outfile);
        }

        outfile.seekp(0);
        outfile.write((char*)(&modelAmount), sizeof(uint8_t));

        outfile.close();
    }

    void packtextures(const aiScene* level, std::ofstream& file){
        textureAmount = level->mNumMaterials;
        for(int i = 0; i < textureAmount; i++){
            aiString texPath;
            level->mMaterials[i]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0,&texPath);

            int textureX, textureY, channels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char* data = stbi_load(texPath.C_Str(), &(textureX), &(textureY), &channels, 4);

            file.write((char*)&textureX, sizeof(uint16_t));
            file.write((char*)&textureY, sizeof(uint16_t));
            file.write((char*)data , textureX*textureY*4);
        }
    }

    void packmodel(const char* modelpath, std::ofstream& file){
        Assimp::Importer importer;
        const aiScene* level = importer.ReadFile(modelpath, aiProcess_OptimizeMeshes);

        packtextures(level, file);

        // aiNode rootNode = level->mRootNode;

        // for(int i = 0; i < rootNode.mNumChildren; i++){
        //     aiNode currNode = rootNode.mChildren[i];


        // }
    }

}
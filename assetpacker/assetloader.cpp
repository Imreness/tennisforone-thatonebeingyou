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
    25 * char - model name
    16 floats - transform matrix
    8bit int - textureID
    32bit int - verticesamount
    float_t  - vertices
    32bit int - indicies amount
    int32 - indicies

*/

namespace assetloader{
    uint8_t textureAmount = 0;
    uint8_t modelAmount = 0;

    void packmodel(const char* modelpath, binaryFile& file);

    void pack(){
        std::printf("Name a subfolder\n");
        std::string subfolder;
        std::getline(std::cin, subfolder);

        std::string path("assets/");
        path.append(subfolder);

        std::string outfilePath("../assets/");
        outfilePath.append(subfolder.c_str()).append(".assetbundle");

        binaryFile outfile;
        outfile.open(outfilePath.c_str(), true);

        const char* placeholder = new char[1];
        //place reserved for texture amount
        outfile.writeChars(placeholder, 1);
        //place reserved for model amount
        outfile.writeChars(placeholder, 1);


        textureAmount = 0;
        modelAmount = 0;
        
        std::printf("Name a file to pack\n");
            
        std::string assetfileName;
        std::getline(std::cin, assetfileName);
        std::string modelpath("assets/");
        modelpath.append(subfolder.c_str()).append("/").append(assetfileName);
        packmodel(modelpath.c_str(), outfile);

        outfile.write(textureAmount, 0);
        outfile.write(modelAmount, 1);

        outfile.close();

        printf("Done packing %s from %s!\n", outfilePath.c_str(), modelpath.c_str());
    }

    void packtextures(const aiScene* level, binaryFile& file, std::string texturepath){
        textureAmount = level->mNumMaterials;
        for(int i = 0; i < textureAmount; i++){
            aiString texPath;
            level->mMaterials[i]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0,&texPath);

            std::string realTexturePath(texturepath);
            realTexturePath.append(texPath.C_Str());

            int textureX, textureY, channels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char* data = stbi_load(realTexturePath.c_str(), &(textureX), &(textureY), &channels, 4);

            file.write((uint16_t)textureX);
            file.write((uint16_t)textureY);
            file.writeChars(data, textureX*textureY*4);
        }
    }

    void packmodel(const char* modelpath, binaryFile& file){
        Assimp::Importer importer;
        const aiScene* level = importer.ReadFile(modelpath, aiProcess_OptimizeMeshes);

        std::string modelpath_string(modelpath);
        std::string modelbasedir = modelpath_string.substr(0, modelpath_string.find_last_of('/') + 1);

        packtextures(level, file, modelbasedir);

        aiNode* rootNode = level->mRootNode;

        for(int i = 0; i < rootNode->mNumChildren; i++){
            modelAmount++;

            aiNode* currNode = rootNode->mChildren[i];

            aiMesh* nodeMesh = level->mMeshes[currNode->mMeshes[0]];

            aiString name = currNode->mName;
            
            file.writeChars(name.C_Str(), 25);

            name.Clear();

            aiMatrix4x4 mat = currNode->mTransformation;
            glm::mat4 transMat = glm::mat4(1.f);

            transMat = glm::transpose(glm::make_mat4(&mat.a1));

            for(int i = 0; i < 4; i++){
                for(int x = 0; x < 4; x++){
                    file.write((float_t)transMat[i][x]);
                }
            }

            file.write((uint8_t)nodeMesh->mMaterialIndex);

            //multiply numvertices with 5, since for each vertices, we got 5 data
            // 3 poisiton and 2 texture coords
            file.write((uint32_t)(nodeMesh->mNumVertices));

            for(int i = 0; i < nodeMesh->mNumVertices; i++){
                file.write((float_t)nodeMesh->mVertices[i].x);
                file.write((float_t)nodeMesh->mVertices[i].y);
                file.write((float_t)nodeMesh->mVertices[i].z);

                file.write((float_t)nodeMesh->mTextureCoords[0][i].x);
                file.write((float_t)(nodeMesh->mTextureCoords[0][i].y));
            }

            file.write((uint32_t)(nodeMesh->mNumFaces));

            for(int i = 0; i < nodeMesh->mNumFaces; i++){
                file.write((uint32_t)nodeMesh->mFaces[i].mIndices[0]);
                file.write((uint32_t)nodeMesh->mFaces[i].mIndices[1]);
                file.write((uint32_t)nodeMesh->mFaces[i].mIndices[2]);
            }
        }
    }

}
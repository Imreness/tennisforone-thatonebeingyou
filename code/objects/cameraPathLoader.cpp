#include <objects/cameraPathLoader.hpp>

#include <fstream>
#include <string>


std::vector<cameraTargetObject>loadCameraPath(const char* filepath){
    std::ifstream file;
    file.open(filepath);

    std::string fileLine("placeholder SUCKAAA");

    while(true){
        std::getline(file, fileLine);
        if(fileLine == ""){
            break;
        }

        cameraTargetObject obj;

    }
}
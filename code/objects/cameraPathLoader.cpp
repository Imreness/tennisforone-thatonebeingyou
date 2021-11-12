#include <objects/cameraPathLoader.hpp>

#include <fstream>
#include <string>
#include <filesystem>
#include <spdlog/spdlog.h>

std::vector<cameraTargetObject>loadCameraPath(const char* filepath){
    std::ifstream file;

    std::filesystem::path fspath(filepath);
    if(!std::filesystem::exists(fspath)){
        spdlog::error("Cannot find .path file at: {}", filepath);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        abort();
    }

    file.open(filepath);

    std::string fileLine("");

    std::vector<cameraTargetObject> returnVector;

    while(true){
        std::getline(file, fileLine);
        if(fileLine == ""){
            break;
        }

        cameraTargetObject obj;

        std::vector<std::string> stringValues;
        std::vector<int> spaces;
        //each line has 8 values

        for(int i = 0; i < fileLine.length(); i++){
            if(fileLine.at(i) == ' '){
                spaces.push_back(i);
            }
        }

        //this could be a loop but fuck that noise this runs like ONCE. ONCE PER STATE! i aint writin good code here .-.

        stringValues.push_back(fileLine.substr(0, spaces.at(0)));
        stringValues.push_back(fileLine.substr(spaces.at(0) + 1, spaces.at(1) - spaces.at(0) - 1));
        stringValues.push_back(fileLine.substr(spaces.at(1) + 1, spaces.at(2) - spaces.at(1) - 1));
        stringValues.push_back(fileLine.substr(spaces.at(2) + 1, spaces.at(3) - spaces.at(2) - 1));
        stringValues.push_back(fileLine.substr(spaces.at(3) + 1, spaces.at(4) - spaces.at(3) - 1));
        stringValues.push_back(fileLine.substr(spaces.at(4) + 1, spaces.at(5) - spaces.at(4) - 1));
        stringValues.push_back(fileLine.substr(spaces.at(5) + 1, spaces.at(6) - spaces.at(5) - 1));

        stringValues.push_back(fileLine.substr(spaces.at(6) + 1));

        obj.cameraPos = glm::vec3(std::stof(stringValues.at(0)), std::stof(stringValues.at(1)), std::stof(stringValues.at(2)));
        obj.cameraLookAt = glm::vec3(std::stof(stringValues.at(3)), std::stof(stringValues.at(4)), std::stof(stringValues.at(5)));

        obj.movementSpeed = std::stof(stringValues.at(6));
        obj.movementTime = std::stof(stringValues.at(7));

        returnVector.push_back(obj);

    }

    return returnVector;
}
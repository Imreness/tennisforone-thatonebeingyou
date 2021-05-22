#include <core/configloader.hpp>
#include <string>

void Configurator::loadConfig(const char* path){
    std::ifstream file; file.open(path);

    std::string line = "hello im the dummy line how are you?";
    
    //it might be a bad idea just to require the config items to be in a certain order but hey,
    //this works and it works fast. Its not a big deal to expect that the end user wont screw the config file up, right?
    std::getline(file, line);
    int value = std::stoi(line.substr(line.find(' ')));
    currentConfig.windowWidth = value;

    std::getline(file, line);
    value = std::stoi(line.substr(line.find(' ')));
    currentConfig.windowHeight = value;

    file.close();

}
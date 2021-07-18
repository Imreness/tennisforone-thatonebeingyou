#include <core/configloader.hpp>
#include <string>

configStruct config::loadConfig(const char* path){
    //spdlog::info("Reading config file...");

    configStruct currentConfig;

    std::ifstream file; file.open(path);

    std::string line = "hello im the dummy line how are you?";
    
    //it might be a bad idea just to require the config items to be in a certain order but hey,
    //this works and it works fast. Its not a big deal to expect that the end user wont screw the config file up, right?

    //get log verboseness
    std::getline(file, line);
    std::string valueString;
    valueString = line.substr(line.find(' ') + 1);
    if(valueString == "DEBUG"){ currentConfig.debuglevel = spdlog::level::debug;}
    else if(valueString == "NORMAL"){ currentConfig.debuglevel = spdlog::level::info;}


    //get the window WIDTH and HEIGHT
    std::getline(file, line);
    int value = std::stoi(line.substr(line.find(' ')));
    currentConfig.windowWidth = value;

    std::getline(file, line);
    value = std::stoi(line.substr(line.find(' ')));
    currentConfig.windowHeight = value;

    //get fullscreen value
    std::getline(file, line);
    valueString.clear(); 
    valueString = line.substr(line.find(' ') + 1);
    if(valueString == "YES"){ currentConfig.fullscreen = true;}
    else if(valueString == "NO"){ currentConfig.fullscreen = false;}

    file.close();

    return currentConfig;

}
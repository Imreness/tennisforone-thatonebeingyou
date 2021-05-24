#include <iostream>
#include <string>
#include <uiloader.cpp>

int main(){
    bool shouldQuit = false;
    std::printf("Welcome to TFOTOBY Assetpacker!\n");

    while(!shouldQuit){
        std::string command;
        std::getline(std::cin , command);

        if(command == "help"){
            std::printf("Current Commands: exit, makeui\n");
        }
        else if(command == "exit"){
            std::printf("Bye!\n");
            shouldQuit = true;
        }
        else if(command == "makeui"){
            std::printf("Specify folder (under assets)\n");
            std::string path;
            std::getline(std::cin, path);
            uipacker::makeui(path);
        }


    }

    return 0;
}
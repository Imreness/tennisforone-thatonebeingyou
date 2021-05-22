#include <fstream>
#include <spdlog/spdlog.h>

struct configStruct{
    int windowWidth;
    int windowHeight;
};

struct Configurator{
    configStruct currentConfig;

    void loadConfig(const char*);

    //TODO - implement this with the settings menu
    void saveConfig(const char*);
};
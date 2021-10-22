#ifndef CONFIGLOADER
#define CONFIGLOADER
#include <fstream>
#include <spdlog/spdlog.h>

struct configStruct{
    int windowWidth;
    int windowHeight;
    bool fullscreen;
    spdlog::level::level_enum debuglevel;
};

//Simple namespace to handle the act of configuration.
//There was once a "saveConfig" method aswell, but given how simple the game is, I dropped the idea of
//having a "Settings Menu".
namespace config{
    configStruct loadConfig(const char*);
};

#endif
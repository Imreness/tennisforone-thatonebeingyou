#include <fstream>
#include <spdlog/spdlog.h>

struct configStruct{
    int windowWidth;
    int windowHeight;
    spdlog::level::level_enum debuglevel;
};

namespace config{
    configStruct loadConfig(const char*);

    //TODO - implement this with the settings menu
    configStruct saveConfig(const char*);
};
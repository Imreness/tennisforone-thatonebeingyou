#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

class Game{
private:

    GLFWwindow* m_mainWindow;

    bool m_shouldRun = true;

public:

    //make debug level config defined
    Game(const char*, spdlog::level::level_enum);

    void update();

    bool shouldRun();
    
    ~Game();

};
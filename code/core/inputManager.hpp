#ifndef INPUTMANAGER
#define INPUTMANAGER

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>

struct key{
    bool m_justPressed;
    bool m_isSticky;

    int m_key;    
};

class InputManager{
private:
    std::unordered_map<std::string, key> m_keys;

public:
    InputManager(){}

    void registerKey(std::string name,int key, bool isSticky = false);

    bool isPressed(std::string name);

    void changeKey(std::string name, int newkey);

};

#endif
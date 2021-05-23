#include <iostream>
#include <core/game.hpp>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
int main(){

    Game TFOTOBY{"Tennis for One - That One Being You"};

    while(TFOTOBY.shouldRun()){
        TFOTOBY.update();
    }

    return 0;
}
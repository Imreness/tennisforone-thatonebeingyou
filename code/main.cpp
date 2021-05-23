#include <iostream>
#include <core/game.hpp>

int main(){

    Game TFOTOBY{"Tennis for One - That One Being You"};

    while(TFOTOBY.shouldRun()){
        TFOTOBY.update();
    }

    return 0;
}
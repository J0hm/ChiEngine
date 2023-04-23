#include <iostream>
#include "Engine.h"
#include "Algorithms.h"

int main() {
    Engine* engine;

    engine = new Engine();
    engine->run();


//    std::string cmd;
//    while (getline(std::cin, cmd)) {
//        std::cout << cmd << std::endl;
//    }

    return 0;
}

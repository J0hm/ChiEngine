#include <iostream>
#include "Engine.cpp"

int main() {
    Engine* engine;

    engine = new Engine();
    engine->run();
    //delete engine;

    return 0;
}

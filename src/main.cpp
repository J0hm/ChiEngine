#include <iostream>
#include "Engine.h"
#include "Algorithms.h"

int main() {
    Engine* engine;

    engine = new Engine();
    engine->run();
    delete engine;

    return 0;
}

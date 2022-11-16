#include <iostream>
#include "Engine.cpp"

int main() {
    ChessEngine* engine;

    engine = new ChessEngine();
    engine->run();
    delete engine;

    return 0;
}

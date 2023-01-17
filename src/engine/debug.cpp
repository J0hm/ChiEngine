#include <iostream>
#include "Engine.h"
#include "Evaluate.h"

int main() {
    Board board;
    Evaluator e = Evaluator("C:/Users/johnk/Documents/Programming/C++/ChiEngine/src/engine/net/evalNN200epoch_scripted.pt");
    std::vector<uint8_t> a;
    std::vector<uint8_t> b;

    for(int i = 0; i < 768; i++) {
        a.push_back(rand()%2);
        b.push_back(rand()%2);
    }

    std::cout << "len: " << a.size() << std::endl;

    std::cout << e.evaluate(a, b) << std::endl;

    return 0;
}

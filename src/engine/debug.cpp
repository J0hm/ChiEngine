#include <iostream>
#include "Engine.h"
#include "Evaluate.h"

int main() {
    Board board;
    Evaluator e = Evaluator("net/evalNN200epoch_scripted.pt");

    return 0;
}

#include "Engine.h"

Engine::Engine() {
    board = new Board();
}

Engine::~Engine() {
    delete board;
}

void Engine::run() {
    while (true) {
        if (!processGuiMessages(500)) break;
    }
}

bool Engine::processGuiMessages(int wait) {
    if (inputThread.isNewInputAvailable()) {
        std::string input = inputThread.getNewInput();
        if (input.length() > 0) {
            return inputHandler(input);
        }
    } else if (wait > 0) Sleep(wait);
    return true;
}

bool Engine::inputHandler(std::string input) {
    std::string command;

    // convert command to a vector
    std::vector<std::string> v;
    Algorithms::split(v, input, " ");


    command = v[0]; // the 1st word is the command id
    if (command == "quit") {
        return false;
    } else if (command == "uci") {
        //sendUCIResponse();
        return true;
    } else {
        std::cout << "info unrecognized command";
        for (std::vector<std::string>::iterator i = v.begin() ; i != v.end(); ++i)
            std::cout << ' ' << *i;
        std::cout << std::endl;
        return true;
    }
}

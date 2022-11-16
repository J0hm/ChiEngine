#include "Engine.h"

void Engine::run() {
    while (true) {
        if (!processGuiMessages(50)) break;
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


    std::stringstream ss(input);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> v(begin, end);

    command = v[0];         // the 1st word is the command id
    if (command == "quit") return false;
    if (command == "uci") {
        sendUCIResponse();
        return true;
    }
    // more commands go here
}

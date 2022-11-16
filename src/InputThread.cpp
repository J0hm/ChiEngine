//
// Created by johnk on 11/16/2022.
//


#include "InputThread.h"

InputThread::InputThread() {
    // start the inputLoop thread
    std::thread t(&InputThread::inputLoop, this);
    t.detach();
}

inline bool InputThread::isNewInputAvailable() {
    return newInputAvailable;
}

std::string InputThread::getNewInput() {
    if (newInputAvailable) {
        newInputAvailable = false;
        return input;
    } else {
        return "";
    }
}

void InputThread::inputLoop() {
    while (true) {
        std::string response;
        std::getline(std::cin, response);
        input = response;
        newInputAvailable = true;
    }
}

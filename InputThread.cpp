#include "InputThread.h"

InputThread::InputThread() {
    // start the inputLoop thread
    std::thread t(&InputThread::inputLoop, this);
    t.detach();
}

void InputThread::inputLoop() {
    while (true) {
        std::string response;
        std::getline(std::cin, response);
        input = response;
        newInputAvailable = true;
    }
}

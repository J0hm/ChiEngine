#ifndef CHIENGINE_ENGINE_H
#define CHIENGINE_ENGINE_H

#include <Windows.h>
#include <vector>
#include <iterator>
#include <sstream>
#include "InputThread.cpp"


class Engine {
public:
    // run the engine
    void run();

private:
    bool inputHandler(std::string input);
    bool processGuiMessages(int wait);
    InputThread inputThread;
};


#endif //CHIENGINE_ENGINE_H

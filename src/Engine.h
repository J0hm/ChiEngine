#ifndef CHIENGINE_ENGINE_H
#define CHIENGINE_ENGINE_H

#include <Windows.h>
#include <vector>
#include <iterator>
#include <sstream>


class Engine {
public:
    // run the engine
    void run();

    bool inputHandler(std::string input);

    bool processGuiMessages(int wait);
};


#endif //CHIENGINE_ENGINE_H

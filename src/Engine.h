#ifndef CHIENGINE_ENGINE_H
#define CHIENGINE_ENGINE_H

#include <Windows.h>
#include <vector>
#include <iterator>
#include <sstream>
#include "InputThread.cpp"

// the main ChessEngine class which "runs" the engine, communicates with the GUI via UCI, and houses all other
// functins of the engine (evaluation, search, etc)
class Engine {
public:
    // run the engine
    void run();

private:
    // handles input from the command line
    // parses and delegates commands
    bool inputHandler(std::string input);

    // processes messages from the UCI GUI
    bool processGuiMessages(int wait);
    InputThread inputThread;
};


#endif //CHIENGINE_ENGINE_H

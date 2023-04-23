#ifndef CHIENGINE_ENGINE_H
#define CHIENGINE_ENGINE_H

#include "InputThread.h"
#include "Search.h"


// the main ChessEngine class which "runs" the engine, communicates with the GUI via UCI, and houses all other
// functions of the engine (evaluation, search, etc)
class Engine {
public:
    // constructor and destructor
    Engine();

    ~Engine();

    // run the engine
    void run();

private:
    void newGame();
    void printOptions();
    void setOption(std::istringstream& is);
    void updatePosition(std::istringstream& is);
    void search(std::istringstream& is);

    InputThread inputThread;
    Board* board;
    Search* searcher;

    bool searching = false;
};


#endif //CHIENGINE_ENGINE_H

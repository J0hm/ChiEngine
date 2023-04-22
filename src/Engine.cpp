#include <Windows.h>
#include <vector>
#include <iterator>
#include <sstream>
#include "Engine.h"
#include "Algorithms.h"

Engine::Engine() {
    this->board = new Board();
    this->searcher = new Search(this->board);
}

Engine::~Engine() {
    delete board;
}

void Engine::run() {
    std::cout << "ChiEngine v1.0 by John Kerr\n";
    while (true) {
        if (!processGuiMessages(500)) break;
    }
}

// process messages from the GUI, if a new input is available
bool Engine::processGuiMessages(int wait) {
    if (inputThread.isNewInputAvailable()) {
        std::string input = inputThread.getNewInput();
        if (input.length() > 0) {
            return inputHandler(input);
        }
    } else if (wait > 0) Sleep(wait);
    return true;
}

// handles commands from the GUI
bool Engine::inputHandler(std::string input) {
    std::string command;

    // convert command to a vector
    std::vector<std::string> v;
    Algorithms::split(v, input, " ");


    command = v[0]; // the 1st word is the command id

    if (command == "quit") {
        return false;
    } else if (command == "uci") {
        sendUCIResponse();
        return true;
    } else if (command == "isready") {
        std::cout << "readyok\n";
        return true;
    } else if (command == "position") {
        if (v[1] == "startpos") {
            board->setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
            if (v.size() > 2 && v[2] == "moves") {
                for (int moveIndex = 3; moveIndex < v.size(); moveIndex++) {
                    board->makeMove(v[moveIndex]);
                }
            }
            return true;
        } else {
            std::cout << "info error does not currently support custom startpos\n";
            return true;
        }
    } else if (command == "go") {
        //TODO fix this
//        if(v[1] == "infinite") {
//            std::cout << "info error does not currently support infinite search depth\n";
//            return true;
//        } else {
//            int depth = std::stoi(v[1]);
//            this->searcher->fixedSearch(depth);
//            Move bestMove = this->searcher->getBestMove();
//            std::cout << "bestmove " << bestMove << " " << this->searcher->getBestMoveEval() << "\n";
//            return true;
//        }
        int depth = 3;
        this->searcher->fixedSearch(depth);
        return true;
    } else if (command == "stop") {
        Move bestMove = this->searcher->getBestMove();
        std::cout << "bestmove " << bestMove << " " << this->searcher->getBestMoveEval() << "\n";
        return true;
    } else {
        std::cout << "info unrecognized command";
        for (std::vector<std::string>::iterator i = v.begin(); i != v.end(); ++i)
            std::cout << ' ' << *i;
        std::cout << "\n";
        return true;
    }
}

void Engine::sendUCIResponse() {
    std::cout << "id name ChiEngine\n";
    std::cout << "id author J0hm\n";
    std::cout << "uciok\n";
}

#include <Windows.h>
#include <vector>
#include <iterator>
#include <iostream>
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
    std::cout << "ChiEngine v1.1 by John Kerr\n";

    std::string cmd;
    std::string token;
    std::cout.setf(std::ios::unitbuf);

    while (getline(std::cin, cmd)) {
        std::istringstream istream(cmd);
        token.clear();
        istream >> std::skipws >> token;

        if (token == "uci") {
            std::cout << "id name ChiEngine\n";
            std::cout << "id author John Kerr\n";
            this->printOptions();
            std::cout << "uciok\n";
        } else if (token == "isready") {
            std::cout << "readyok\n";
        } else if (token == "setoption") {
            setOption(istream);
        } else if (token == "ucinewgame") {
            this->newGame();
        } else if (token == "position") {
            this->updatePosition(istream);
        } else if (token == "go") {
            this->search(istream);
        } else if (token == "stop") {
            this->searching = false;
            Move bestMove =  this->searcher->getBestMove();
            std::cout << "bestmove " << bestMove << std::endl;//<< " " << this->searcher->getBestMoveEval() << std::endl;
        } else if (token == "quit") {
            std::cout << "info terminating\n";
            break;
        } else {
            std::cout << "info unrecognized command\n";
        }
    }
}

void Engine::printOptions() {
    std::cout << "option name TableSize type int default 32\n";
}

void Engine::setOption(std::istringstream &is) {
    // TODO: implement setOption
    std::cout << "info error set option is not net supported\n";
}

void Engine::newGame() {
    this->searching = false;
    board->setFEN(Board::startingFEN);
    this->searcher->resetTable();
}

void Engine::updatePosition(std::istringstream &is) {
    this->searching = false;
    std::string token, fen;

    is >> token;

    if (token == "startpos") {
        this->board->setFEN(Board::startingFEN);
    } else if (token == "fen") {
        while (is >> token && token != "moves") {
            fen += token + " ";
        }

        this->board->setFEN(fen);
    } else {
        return;
    }

    // Parse move list (if any)
    while (is >> token) {
        if (token != "moves") {
            this->board->makeMove(token);
        }
    }
}

void Engine::search(std::istringstream& is) {
    std::string mode;
    is >> mode;

    if(mode == "depth") {
        std::string depthStr;
        is >> depthStr;
        int depth = std::stoi(depthStr);
        this->searcher->negaMaxRoot(depth);
        Move best = this->searcher->getBestMove();
        std::cout << "info searched " << this->searcher->visitedNodes << " nodes, " << this->searcher->collisions << " collisions." << std::endl;
        std::cout << "bestmove " << best << std::endl;
    } else {
        std::cout << "info error unsupported search mode: " << mode << "\n";
    }

}

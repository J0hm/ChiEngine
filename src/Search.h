#ifndef CHIENGINE_SEARCH_H
#define CHIENGINE_SEARCH_H

#include <algorithm>
#include "Eval.h"
#include "TTable.h"

class Search {
public:
    // constructor
    explicit Search(Board* board);

    // get the best move and its evaluation
    Move getBestMove();
    int getBestMoveEval();

    // searches to a fixed depth, does not support timing, threading, stopping
    // the search early, etc
    int negaMaxRoot(int depth);

    int iterativeDeepeningRoot(int depth);

    void resetTable();

    int visitedNodes;
    int collisions;


private:
    Eval* evaluator;
    Board* gameBoard;
    TTable* table;
    Move bestMove;
    int bestMoveRating{};
    int negaMax(int depth, int alpha, int beta);
    int quiesce(int alpha, int beta);

};

#endif //CHIENGINE_SEARCH_H

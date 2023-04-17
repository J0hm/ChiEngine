#ifndef CHIENGINE_SEARCH_H
#define CHIENGINE_SEARCH_H

#include "Eval.h"

class Search {
public:
    // constructor
    explicit Search(Board* board);

    // get the best move and its evaluation
    Move getBestMove() const;
    int getBestMoveEval() const;

    // searches to a fixed depth, does not support timing, threading, stopping
    // the search early, etc
    void fixedSearch(int depth);

private:
    Eval* evaluator;
    Board* gameBoard;
    Move bestMove;
    int bestMoveRating{};
    int visitedNodes;

    int alphaBeta(int alpha, int beta, int depth);
    int quiesce( int alpha, int beta);
};

#endif //CHIENGINE_SEARCH_H

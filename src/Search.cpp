#include "Search.h"

Search::Search(Board *board) {
    this->gameBoard = board;
    this->evaluator = new Eval(board);
    this->bestMoveRating = 0;
    this->visitedNodes = 0;
}

Move Search::getBestMove() const {
    return this->bestMove;
}

int Search::getBestMoveEval() const {
    return this->bestMoveRating;
}

void Search::fixedSearch(int depth) {
    std::cout << "Search started..." << std::endl;
    this->visitedNodes = 0;
    this->bestMoveRating = alphaBetaMax(INT_MIN+1, INT_MAX-1, depth);
    std::cout << "Evaluated " << this->visitedNodes << " nodes to reach depth " << depth
              << " and find move with eval " << this->bestMoveRating << std::endl;

}

int Search::quiesce(int alpha, int beta) {
    this->visitedNodes++;
    int stand_pat = this->evaluator->evaluate();

    if (stand_pat >= beta) return beta;
    if (alpha < stand_pat) alpha = stand_pat;

    std::vector<Move> captures = this->gameBoard->movegen->getCaptures();

    for (Move m: captures) {
        this->gameBoard->makeMove(m);
        int score = -quiesce(-beta, -alpha);
        this->gameBoard->unmakeMove();

        if (score >= beta)
            return beta;
        if (score > alpha)
            alpha = score;
    }
    return alpha;
}

int Search::alphaBeta(int alpha, int beta, int depth) {
    if (depth == 0) {
        return quiesce(alpha, beta);
    }
    std::vector<Move> moves = this->gameBoard->movegen->getLegalMoves();

    for (Move m: moves) {
        this->gameBoard->makeMove(m);
        int score = -alphaBeta(-beta, -alpha, depth - 1);
        this->gameBoard->unmakeMove();
        if (score >= beta)
            return beta;
        if (score > alpha)
            alpha = score;
    }
    return alpha;
}

int Search::alphaBetaMax(int alpha, int beta, int depth) {
    if (depth == 0) {
        this->visitedNodes++;
        return this->evaluator->evaluate();
    }

    std::vector<Move> moves = this->gameBoard->movegen->getLegalMoves();

    for (Move m : moves) {
        this->gameBoard->makeMove(m);
        int score = alphaBetaMin( alpha, beta, depth - 1 );
        this->gameBoard->unmakeMove();
        if( score >= beta )
            return beta;   // fail hard beta-cutoff
        if( score > alpha ) {
            bestMove = m;
            alpha = score; // alpha acts like max in MiniMax
        }

    }
    return alpha;
}

int Search::alphaBetaMin(int alpha, int beta, int depth) {
    if (depth == 0) {
        this->visitedNodes++;
        return -this->evaluator->evaluate();
    }

    std::vector<Move> moves = this->gameBoard->movegen->getLegalMoves();

    for (Move m : moves) {
        this->gameBoard->makeMove(m);
        int score = alphaBetaMax( alpha, beta, depth - 1 );
        this->gameBoard->unmakeMove();
        if( score <= alpha )
            return alpha; // fail hard alpha-cutoff
        if( score < beta ) {
            //bestMove = m;
            beta = score; // beta acts like min in MiniMax
        }

    }
    return beta;
}

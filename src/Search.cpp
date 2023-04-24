#include "Search.h"

Search::Search(Board *board) {
    this->gameBoard = board;
    this->evaluator = new Eval(board);
    this->bestMoveRating = 0;
    this->visitedNodes = 0;
    this->table = new TTable();
}

Move Search::getBestMove() {
    return this->bestMove;
//    int64 currHash = gameBoard->getLastState().hash; // TODO refactor, getHash
//    Transposition tableEntry = table->getEntry(currHash);
//    if(tableEntry.hasEntry) {
//        Move m = tableEntry.bestMove;
//        std::cout << "has best move entry" << std::endl;
//        return m;
//    } else {
//        std::cout << "does not have best move" << std::endl;
//        return Move();
//    }
}

int Search::getBestMoveEval() {
    return this->bestMoveRating;
}

int Search::negaMaxRoot(int depth) {
    int alpha = -999999;
    int beta = -alpha;
    int score = 0;
    visitedNodes = 0;
    collisions = 0;

    int64 currHash = gameBoard->getLastState().hash; // TODO refactor, getHash
    Transposition tableEntry = table->getEntry(currHash);
    bool valid = tableEntry.hasEntry && tableEntry.depth > depth;

    if (valid) {
        if (tableEntry.hash == currHash) {
            if (tableEntry.hashType == HASH_EXACT) { // not nullptr, i.e. have a match w/ greater depth
                this->bestMove = tableEntry.bestMove;
                return tableEntry.eval;
            }
        } else {
            collisions++;
        }
    }


    std::vector<Move> moveList = this->gameBoard->movegen->getLegalMoves(); // TODO refactor
    for (Move m: moveList) {
        this->gameBoard->makeMove(m);
        score = -negaMax(depth - 1, -beta, -alpha);
        this->gameBoard->unmakeMove();

        if (score > alpha) {
            alpha = score;
            this->bestMove = m;
        }
    }

    this->table->setTTEntry(gameBoard->getLastState().hash, HASH_EXACT, depth, alpha, this->bestMove);

    return alpha;
}

int Search::negaMax(const int depth, int alpha, const int beta) {
    int alpha_old = alpha;

    if (depth <= 0) {
        if(gameBoard->getLastState().move.isCapture()) { // TODO may need to be second to last state
            return quiesce(alpha, beta);
        } else {
            visitedNodes++;
            return this->evaluator->evaluate();
        }
    }

    int64 currHash = gameBoard->getLastState().hash; // TODO refactor, getHash
    Transposition tableEntry = table->getEntry(currHash);
    bool valid = tableEntry.hasEntry && tableEntry.depth > depth;

    if (valid) {
        if (tableEntry.hash == currHash) {
            if (tableEntry.hashType == HASH_EXACT) { // not nullptr, i.e. have a match w/ greater depth
                return tableEntry.eval;
            } else if (tableEntry.hashType == HASH_BETA && tableEntry.eval <= alpha) { // beta = HIGH CUT OFF
                return alpha;
            } else if (tableEntry.hashType == HASH_ALPHA && tableEntry.eval >= beta) { // alpha = LOW CUT OFF
                return beta;
            }
        } else {
            collisions++;
        }
    }


    // TODO stalemate/checkmate

    int score = 0;
    Move localBestMove = Move();
    int bestScore = -999999;

    std::vector<Move> moveList = this->gameBoard->movegen->getLegalMoves(); // TODO refactor
    for (Move m: moveList) {
        this->gameBoard->makeMove(m);
        score = -negaMax(depth - 1, -beta, -alpha);
        this->gameBoard->unmakeMove();

        if (score >= beta) {
            this->table->setTTEntry(gameBoard->getLastState().hash, HASH_ALPHA, depth, score, m);
            return beta;
        }

        if (score > bestScore) {
            bestScore = score;
            localBestMove = m;
            if (score > alpha) {
                alpha = score;
            }
        }
    }

    if (alpha > alpha_old) {
        this->table->setTTEntry(gameBoard->getLastState().hash, HASH_EXACT, depth, bestScore, localBestMove);
    } else {
        this->table->setTTEntry(gameBoard->getLastState().hash, HASH_BETA, depth, alpha, localBestMove);
    }

    return alpha;
}

int Search::quiesce(int alpha, int beta) {
    int standPat = this->evaluator->evaluate();
    visitedNodes++;

    if (standPat >= beta) {
        return beta;
    } else if (alpha < standPat) {
        alpha = standPat;
    }

    std::vector<Move> moveList = this->gameBoard->movegen->getLegalMoves(); // TODO refactor
    for (Move m: moveList) {
        if (m.isCapture()) {
            int score = 0;
            gameBoard->makeMove(m);
            score = -quiesce(-beta, -alpha);
            gameBoard->unmakeMove();

            if (score >= beta) {
                return beta;
            } else if (score > alpha) {
                alpha = score;
            }
        }
    }

    return alpha;
}

void Search::resetTable() {
    table->reset();
}




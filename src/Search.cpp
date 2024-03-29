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
                this->bestMoveRating = tableEntry.eval;
                return this->bestMoveRating;
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
            this->bestMoveRating = alpha;
            this->bestMove = m;
        }
    }

    Transposition entry = table->getEntry(gameBoard->getLastState().hash);
    if(!entry.hasEntry || entry.depth < depth)
        this->table->setTTEntry(gameBoard->getLastState().hash, HASH_EXACT, depth, alpha, this->bestMove);

    return alpha;
}

int Search::negaMax(const int depth, int alpha, const int beta) {
    int alpha_old = alpha;

    if (depth <= 0) {
        Move lastMove = gameBoard->getLastState().move;
        if(lastMove.isCapture()) {
            return quiesce(alpha, beta); // quiesce on captures to avoid horizon effect
        } else {
            visitedNodes++;
            return this->evaluator->evaluate();
        }
    }

    int64 currHash = gameBoard->getLastState().hash; // TODO refactor, getHash

    // check for repetition
    std::vector<int64> keys = gameBoard->getKeyHistory();
    keys.pop_back();
    if (std::find(keys.begin(), keys.end(), currHash) != keys.end()) {
        return DRAW_SCORE;
    }


    // use table entry if it exists and is valid
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

    int score = 0;
    Move localBestMove = Move();
    int bestScore = -999999;

    std::vector<Move> moveList = this->gameBoard->movegen->getLegalMoves(); // TODO refactor
    if(moveList.empty()) { // MATE or DRAW
        if(this->gameBoard->movegen->inCheck(this->gameBoard->sideToMove)) { // TODO
            return -(MATE_SCORE+depth); // closer to root = depth is higher = weighted more (we want shortest mates)
        } else {
            return DRAW_SCORE;
        }
    }

    // go over each move
    for (Move m: moveList) {
        this->gameBoard->makeMove(m);
        score = -negaMax(depth - 1, -beta, -alpha);
        this->gameBoard->unmakeMove();

        if (score >= beta) {
            Transposition entry = table->getEntry(gameBoard->getLastState().hash);
            if(!entry.hasEntry || entry.depth < depth) // store alpha cutoff
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
        Transposition entry = table->getEntry(gameBoard->getLastState().hash);
        if(!entry.hasEntry || entry.depth < depth) // store EXACT since we are between alpha and beta
            this->table->setTTEntry(gameBoard->getLastState().hash, HASH_EXACT, depth, bestScore, localBestMove);
    } else {
        Transposition entry = table->getEntry(gameBoard->getLastState().hash);
        if(!entry.hasEntry || entry.depth < depth) // store beta cutoff
            this->table->setTTEntry(gameBoard->getLastState().hash, HASH_BETA, depth, alpha, localBestMove);
    }

    return alpha;
}

// search only captures
int Search::quiesce(int alpha, int beta) {
    int standPat = this->evaluator->evaluate();
    visitedNodes++;

    if (standPat >= beta) { // good enough, return
        return beta;
    } else if (alpha < standPat) { // set alpha cutoff
        alpha = standPat;
    }

    std::vector<Move> moveList = this->gameBoard->movegen->getLegalMoves(); // TODO refactor
    for (Move m: moveList) {
        Move lastMove = this->gameBoard->getLastState().move;
        bool recapture = m.getDest() == lastMove.getDest();
        if (m.isCapture() && recapture) { // search only recaptures...
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

//int Search::iterativeDeepeningRoot(int depth) {
//    int nodes = 0;
//    int totalCollisions = 0;
//    for(int i = 0; i < depth; i++) {
//        negaMaxRoot(i);
//        nodes += visitedNodes;
//        totalCollisions += collisions;
//    }
//
//    visitedNodes = nodes;
//    collisions = totalCollisions;
//    return negaMaxRoot(depth);
//}

// reset the transposition table (sets all hasValue to false
void Search::resetTable() {
    table->reset();
}






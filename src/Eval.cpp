#include "Eval.h"

Eval::Eval(Board *board) {
    this->gameBoard = board;
    this->initTables();
}

void Eval::initTables() {
    for (EPiece pc = B_PAWN; pc <= B_KING; pc++) {
        for (int sq = 0; sq < 64; sq++) {
            PieceType type = getPieceType(pc);
            mg_table[pc-1]  [sq] = MG_VALUE[type] + MG_PESTO_TABLE[type][sq];
            eg_table[pc-1]  [sq] = EG_VALUE[type] + EG_PESTO_TABLE[type][sq];
        }
    }

    for (EPiece pc = W_PAWN; pc <= W_KING; pc++) {
        for (int sq = 0; sq < 64; sq++) {
            PieceType type = getPieceType(pc);
            mg_table[pc-1][sq] = MG_VALUE[type] + MG_PESTO_TABLE[type][FLIP(sq)];
            eg_table[pc-1][sq] = EG_VALUE[type] + EG_PESTO_TABLE[type][FLIP(sq)];
        }
    }

    std::cout << "Initialized eval tables...\n";
}

// from CPW
int Eval::evaluate() {
    EColor sideToMove = this->gameBoard->sideToMove;

    int mg[2];
    int eg[2];
    int gamePhase = 0;

    mg[WHITE] = 0;
    mg[BLACK] = 0;
    eg[WHITE] = 0;
    eg[BLACK] = 0;

    // eval each piece
    for (int sq = 0; sq < 64; sq++) {
        EPiece pc = this->gameBoard->bb.squares[sq];
        if (pc != EMPTY) {
            mg[pieceColor(pc)] += mg_table[pc-1][sq];
            eg[pieceColor(pc)] += eg_table[pc-1][sq];
            gamePhase += gamephaseInc[pc];
        }
    }

    // tapered eval
    int mgScore = mg[sideToMove] - mg[OTHER(sideToMove)];
    int egScore = eg[sideToMove] - eg[OTHER(sideToMove)];
    int mgPhase = gamePhase;
    if (mgPhase > 24) mgPhase = 24; // early promotion
    int egPhase = 24 - mgPhase;
    return (mgScore * mgPhase + egScore * egPhase) / 24;
}


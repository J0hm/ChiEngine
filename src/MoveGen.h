#ifndef CHIENGINE_MOVEGEN_H
#define CHIENGINE_MOVEGEN_H

#include "Types.h"
#include "Board.h"
#include "MagicMoves.h"

class Board;
// pre-initialize attacks for knights
// magic bitboards for bishop/rook, NEED: int64 mask, int64 magic number for each square for rook/bishop
// probably want to add popLSB/getLSB, also might want to move the others from board.h to types.h
// want: isLegal(Move), MoveGen initialized with a pointer to the board
// get attacks for each piece
// enum for EVASIONS, LEGAL, PSEUDO_LEGAL?
// efficient checking for checks, check if a move puts the king in check
class MoveGen {
public:
    MoveGen(Board* board) {
        this->board = board;
        magic = new MagicMoves;
        magic->initMagics();
        initKnightAttackTable();
    }

    EBitBoard allAttackBitBoard[2];

    // is the given move a legal move for the board state?
    bool isLegal(Move m);

    // get all pseudo-legal moves of the given piece type, based on turn of board
    // TODO move to private or add call to calcAttackBitboard to function
    std::vector<Move> getPawnMoves();
    std::vector<Move> getKnightMoves();
    std::vector<Move> getRookMoves();
    std::vector<Move> getBishopMoves();
    std::vector<Move> getQueenMoves();
    std::vector<Move> getKingMoves();

    // get all the legal moves
    std::vector<Move> getLegalMoves();

    // get all moves which will resolve the check
    std::vector<Move> getEvasions();

    void calcAllAttackBitboard(EColor side);

    // determines if the board is in check
    bool inCheck(EColor side);

    // does this move cause a check to a certain color?
    bool doesCheck(Move m, EColor toColor);

    // does this move resolve a check?
    bool resolvesCheck(Move m);


private:
    int64 knightAttackTable[64]; // attack table for all possible knight positions, precalculated
    Board* board;
    MagicMoves* magic;

    // attack bitboard for each color, must be calculated first. 0 = white, 1 = black
    EBitBoard pawnAttackBitBoard[2];
    EBitBoard knightAttackBitboard[2];
    EBitBoard bishopAttackBitBoard[2];
    EBitBoard rookAttackBitBoard[2];
    EBitBoard queenAttackBitBoard[2];
    EBitBoard kingAttackBitboard[2];


    void initKnightAttackTable();

    // calculate and update bitboards for piece attacks for the given side
    void calcPawnAttackBitboard(EColor side); // does not have all pawn moves, only capture threats not incl. en passant
    void calcKnightAttackBitboard(EColor side);
    void calcBishopAttackBitboard(EColor side);
    void calcRookAttackBitboard(EColor side);
    void calcQueenAttackBitboard(EColor side);
    void calcKingAttackBitboard(EColor side); // does not include castling
};


#endif //CHIENGINE_MOVEGEN_H

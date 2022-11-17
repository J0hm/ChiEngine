//
// Created by johnk on 11/16/2022.
//

#ifndef CHIENGINE_BOARD_H
#define CHIENGINE_BOARD_H

#include "Types.h";

// Holds the piece location status of the board in BitBoards per Piece
// This is a hybrid approach
struct BoardBB
{
    // Holds the piece information per square
    EPiece squares[H8+2];
    // BitBoards for Pieces
    EBitBoard pcs[B_KING+2];
    // Utility BitBoards
    EBitBoard emptySquares;
    EBitBoard occupiedSquares;
    EBitBoard pcsOfColor[BLACK+1];
};

struct BoardState
{
    int64 hash;
    int lastTriggerEvent; // ply whith pawn move or capture
    int castlingRights;
    ESquare enPassantSquare;
    EMove move;
    bool inCheck;
    int repetitions;
};

class Board {
public:
    BoardBB bb;
    EColor sideToMove;
    int currentPly;

    Board();
    ~Board();
private:
    BoardStateHistory *boardHistory; // pointer to list of BoardState objects
}


#endif //CHIENGINE_BOARD_H

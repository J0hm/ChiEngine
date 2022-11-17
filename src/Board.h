#ifndef CHIENGINE_BOARD_H
#define CHIENGINE_BOARD_H

#include <string>
#include <vector>
#include "Types.h"
#include "Algorithms.h"

// Holds the piece location status of the board in BitBoards per Piece
// This is a hybrid approach
struct BoardBB {
    // Holds the piece information per square
    EPiece squares[H8 + 2];
    // BitBoards for Pieces
    EBitBoard pcs[B_KING + 2];
    // Utility BitBoards
    EBitBoard emptySquares;
    EBitBoard occupiedSquares;
    EBitBoard pcsOfColor[BLACK + 1];
};

struct BoardState {
    int64 hash;
    int lastTriggerEvent; // ply with pawn move or capture
    int castlingRights; // 4 bits: KQkq = 1111, Kk = 1010, Kq = 1001, etc
    ESquare enPassantSquare;
    //EMove move; TODO make move class
    bool inCheck;
    int repetitions;
};

class BoardStateHistory {
public:
    void initialize(unsigned int c, ESquare sq);

private:
    std::vector<BoardState> stateList;
    int64 bbSquares(ESquare sq);
};

class Board {
public:
    BoardBB bb;
    EColor sideToMove;
    int currentPly;

    Board();

    ~Board();

    // set the board to the position specified by the given FEN
    int setFEN(std::string fen);

private:
    BoardStateHistory *boardHistory; // list of BoardState objects representing the history of the board
    void initializeBitBoards();
};

#endif //CHIENGINE_BOARD_H
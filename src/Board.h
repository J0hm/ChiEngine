#ifndef CHIENGINE_BOARD_H
#define CHIENGINE_BOARD_H

#include <string>
#include <vector>
#include "Move.h"

#define set_bit(b, i) ((b) |= (1ULL << i))
#define get_bit(b, i) ((b) & (1Ull << i))
#define clear_bit(b, i) ((b) &= ~(1Ull << i))

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

// Represents the state of the board after the given move
struct BoardState {
    int64 hash; // hash for the board, used to find already-evaluated positions
    int lastTriggerEvent; // ply with pawn move or capture
    int castlingRights; // 4 bits: KQkq = 1111, Kk = 1010, Kq = 1001, etc
    ESquare enPassantSquare; // square which can be moved to in order to capture via en passant
    Move move;
    bool inCheck; // is a player in check?
    int repetitions; // number of times the same position was visited
};

// Represents the history of the board state
class BoardStateHistory {
public:
    // Initialize the board state with the given castling rights and en passant square
    void initialize(unsigned int c, ESquare sq);

    // Get the last state of the board
    inline BoardState getLastState() {return stateList.back();}

    // Pop the last state from the list
    inline BoardState popLastState() {
        BoardState back = stateList.back();
        stateList.pop_back();
        return back;
    }

    // add a state to the board state
    inline void addState(BoardState s) {stateList.push_back(s);};

    int getStateCount() {return stateList.size();};

private:
    std::vector<BoardState> stateList;
};

// Represents the actual game board
class Board {
public:
    // BitBoard for this board
    BoardBB bb;
    EColor sideToMove;
    int currentPly;

    Board();

    ~Board();

    // Set the board to the position specified by the given FEN
    int setFEN(std::string fen);

    // Parse a move in long algebraic notation using the current board state
    Move parseMove(std::string lan);

    // Make a move
    void makeMove(Move move);
    inline void makeMove(std::string lan) {makeMove(parseMove(lan));}

    // Unmake a move
    void unmakeMove();

    // Get the last state of the board
    inline BoardState getLastState() { return boardHistory->getLastState();};

    // Pop the last boardstate off of the list
    inline BoardState popBoardState() {return boardHistory->popLastState();};

    // get the number of stored board states
    inline int getStateCount() {return boardHistory->getStateCount();};


private:
    BoardStateHistory *boardHistory; // list of BoardState objects representing the history of the board
    void initializeBitBoards();

    // gets a square from file and rank characters
    ESquare getSquare(char file, char rank);
};

#endif //CHIENGINE_BOARD_H
#ifndef CHIENGINE_BOARD_H
#define CHIENGINE_BOARD_H

#include <string>
#include <utility>
#include <vector>
#include "Move.h"
#include "MoveGen.h"
#include "ZobristHasher.h"

class MoveGen;

// Represents the state of the board after the given move
struct BoardState {
    int64 hash; // hash for the board, used to find already-evaluated positions
    int lastTriggerEvent; // ply with pawn move or capture
    unsigned int castlingRights; // 4 bits: KQkq = 1111, Kk = 1010, Kq = 1001, etc
    ESquare enPassantSquare; // square which can be moved to in order to capture via en passant
    Move move;
    bool inCheck; // is a player in check?
    int repetitions; // number of times the same position was visited
};

// Represents the history of the board state
class BoardStateHistory {
public:
    // Initialize the board state with the given castling rights and en passant square
    void initialize(unsigned int c, ESquare sq, int64 hash);

    // Get the last state of the board
    inline BoardState getLastState() { return stateList.back(); }

    // Pop the last state from the list
    inline BoardState popLastState() {
        BoardState back = stateList.back();
        stateList.pop_back();
        keyList.pop_back();
        return back;
    }

    // add a state to the board state
    inline void addState(BoardState s) {
        stateList.push_back(s);
        keyList.push_back(s.hash);
    };

    int getStateCount() { return stateList.size(); };

    std::vector<int64> getKeyHistory();

private:
    std::vector<BoardState> stateList;
    std::vector<int64> keyList;
};

// Represents the actual game board
class Board {
public:
    // BitBoard for this board
    BoardBB bb{};
    MoveGen *movegen;
    EColor sideToMove;
    int currentPly{};

    Board();

    ~Board();

    // Set the board to the position specified by the given FEN
    int setFEN(std::string fen);

    // Parse a move in long algebraic notation using the current board state
    Move parseMove(std::string lan);

    // Make a move
    void makeMove(Move move);

    inline void makeMove(std::string lan) { makeMove(parseMove(std::move(lan))); }

    // Unmake a move
    void unmakeMove();

    // Get the last state of the board
    inline BoardState getLastState() { return boardHistory->getLastState(); };

    // Pop the last boardstate off of the list
    inline BoardState popBoardState() {
        return boardHistory->popLastState();
    };

    // get the number of stored board states
    inline int getStateCount() { return boardHistory->getStateCount(); };

    // get the piece at a square
    inline EPiece getPieceAt(ESquare sq) { return this->bb.squares[sq]; }

    std::vector<int64> getKeyHistory();

    // returns the total number of moves to the specified depth
    int64 perft(int depth, int depthToShow);

    static BoardBB copyBB(BoardBB bb);

    static bool bbEqual(BoardBB bb1, BoardBB bb2);

    static const std::string startingFEN;


private:
    BoardStateHistory *boardHistory; // list of BoardState objects representing the history of the board

    ZobristHasher hasher;

    void initializeBitBoards();

    // gets a square from file and rank characters
    static ESquare getSquare(char file, char rank);

    // clears the piece at a given square
    void clearSquare(int sq, EPiece piece, EColor side);

    void setSquare(int sq, EPiece piece, EColor side);
};

#endif //CHIENGINE_BOARD_H
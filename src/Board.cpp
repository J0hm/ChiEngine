#include "Board.h"

Board::Board() {

}

Board::~Board() {

}

// set the board to the position specified by the given FEN
int Board::setFEN(std::string FEN) {
    unsigned int i, j, castle;
    ESquare sq;
    char letter;
    int aRank, aFile;
    std::vector<std::string> strList;
    Algorithms::split(strList, FEN, " ");

    // empty the board squares
    for (sq = A1; sq <= H8; sq++) bb.squares[sq] = EMPTY;
    // read the board - translate each loop index into a square
    j = 1; // go through board in dir of fen
    i = 0; // curr pos in fen string
    while ((j <= 64) && (i <= strList[0].length())) {
        letter = strList[0].at(i);
        i++;
        aFile = 1 + ((j - 1) % 8);
        aRank = 8 - ((j - 1) / 8);
        sq = (ESquare) (((aRank - 1) * 8) + (aFile - 1));
        switch (letter) {
            case 'p' :
                bb.squares[sq] = B_PAWN;
                break;
            case 'r' :
                bb.squares[sq] = B_ROOK;
                break;
            case 'n' :
                bb.squares[sq] = B_KNIGHT;
                break;
            case 'b' :
                bb.squares[sq] = B_BISHOP;
                break;
            case 'q' :
                bb.squares[sq] = B_QUEEN;
                break;
            case 'k' :
                bb.squares[sq] = B_KING;
                break;
            case 'P' :
                bb.squares[sq] = W_PAWN;
                break;
            case 'R' :
                bb.squares[sq] = W_ROOK;
                break;
            case 'N' :
                bb.squares[sq] = W_KNIGHT;
                break;
            case 'B' :
                bb.squares[sq] = W_BISHOP;
                break;
            case 'Q' :
                bb.squares[sq] = W_QUEEN;
                break;
            case 'K' :
                bb.squares[sq] = W_KING;
                break;
            case '/' :
                j--;
                break;
            case '1' :
                break;
            case '2' :
                j++;
                break;
            case '3' :
                j += 2;
                break;
            case '4' :
                j += 3;
                break;
            case '5' :
                j += 4;
                break;
            case '6' :
                j += 5;
                break;
            case '7' :
                j += 6;
                break;
            case '8' :
                j += 7;
                break;
            default:
                return -1;
        }
        j++;
    }

    // set the turn; default = White
    sideToMove = WHITE;
    if (strList.size() >= 2) {
        if (strList[1] == "w") sideToMove = WHITE;
        else if (strList[1] == "b") sideToMove = BLACK; else return -1;
    }

    // set castle possibilities to initial 0
    castle = 0;
    // initialize all castle possibilities
    if (strList.size() >= 3) {
        if (strList[2].find('K') != std::string::npos)
            castle |= 0b1000;
        if (strList[2].find('Q') != std::string::npos)
            castle |= 0b0100;
        if (strList[2].find('k') != std::string::npos)
            castle |= 0b0010;
        if (strList[2].find('q') != std::string::npos)
            castle |= 0b0001;
    }

    // read en passant and save it into "sq" Default := None (ER)
    sq = ER;
    if ((strList.size() >= 4) && (strList[3].length() >= 2)) {
        if ((strList[3].at(0) >= 'a') && (strList[3].at(0) <= 'h') &&
            ((strList[3].at(1) == '3') || (strList[3].at(1) == '6'))) {
            aFile = strList[3].at(0) - 96; // ASCII 'a' = 97
            aRank = strList[3].at(1) - 48; // ASCII '1' = 49
            sq = (ESquare) ((aRank - 1) * 8 + aFile - 1);
        } else return -1;
    }

    // we start at turn 1 per default
    currentPly = 1;
    if (strList.size() >= 6) {
        currentPly = 2 * (std::stoi(strList[5]) - 1) + 1;
        if (currentPly < 0) currentPly = 0; // avoid possible underflow
        if (sideToMove == BLACK) currentPly++;
    }

    // initialize the board state history stack
    boardHistory->initialize(castle, sq);
    // set up the piece related bit boards with this board content
    initializeBitBoards();
    return 0;
}

void BoardStateHistory::initialize(unsigned int c, ESquare sq) {
    BoardState state;
    state.enPassantSquare = sq;
    state.castlingRights = c;
    stateList.push_back(state);
}

int64 bbSquares(ESquare sq){
    return (int64)1 << (8*(sq / 8) - (sq % 8) + 7);
}

void Board::initializeBitBoards() {
    ESquare sq;
    memset(&bb.pcs,0,sizeof(bb.pcs));
    // initialize the piece bit boards...
    for (sq=A1;sq<=H8;sq++)
        bb.pcs[bb.squares[sq]] |= bbSquares(sq);
    // calculate the utility bitboards...
    bb.pcsOfColor[WHITE] = bb.pcs[W_PAWN] | bb.pcs[W_KNIGHT] | bb.pcs[W_BISHOP] |
                           bb.pcs[W_ROOK] | bb.pcs[W_QUEEN] | bb.pcs[W_KING];
    bb.pcsOfColor[BLACK] = bb.pcs[B_PAWN] | bb.pcs[B_KNIGHT] | bb.pcs[B_BISHOP] |
                           bb.pcs[B_ROOK] | bb.pcs[B_QUEEN] | bb.pcs[B_KING];
    bb.occupiedSquares = bb.pcsOfColor[WHITE] | bb.pcsOfColor[BLACK];
    bb.emptySquares = ~bb.occupiedSquares;
}


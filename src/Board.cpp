#include <iostream>
#include <array>
#include <sstream>
#include <cstring>
#include "Board.h"
#include "Algorithms.h"

Board::Board() {
    boardHistory = new BoardStateHistory(); // initialize pointer to BoardStateHistory
}

Board::~Board() {

}

// set the board to the position specified by the given FEN
int Board::setFEN(std::string FEN) {
    unsigned int i, j, castle;
    ESquare sq;
    char letter;
    unsigned int aRank, aFile;
    std::vector<std::string> strList;
    Algorithms::split(strList, FEN, " ");

    std::cout << "Setting fen to " << FEN << std::endl;

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

    // set the turn; default = WHITE
    sideToMove = WHITE;
    if (strList.size() >= 2) {
        if (strList[1] == "w") sideToMove = WHITE;
        else if (strList[1] == "b") sideToMove = BLACK;
        else return -1;
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

// initialize the utility BitBoards after setting the squares
void Board::initializeBitBoards() {
    ESquare sq;
    memset(&bb.pcs, 0, sizeof(bb.pcs));
    // initialize the piece bit boards...
    for (sq = A1; sq <= H8; sq++)
        bb.pcs[bb.squares[sq]] |= BB_SQUARES[sq];
    // calculate the utility bitboards...
    bb.pcsOfColor[WHITE] = bb.pcs[W_PAWN] | bb.pcs[W_KNIGHT] | bb.pcs[W_BISHOP] |
                           bb.pcs[W_ROOK] | bb.pcs[W_QUEEN] | bb.pcs[W_KING];
    bb.pcsOfColor[BLACK] = bb.pcs[B_PAWN] | bb.pcs[B_KNIGHT] | bb.pcs[B_BISHOP] |
                           bb.pcs[B_ROOK] | bb.pcs[B_QUEEN] | bb.pcs[B_KING];
    bb.occupiedSquares = bb.pcsOfColor[WHITE] | bb.pcsOfColor[BLACK];
    bb.emptySquares = ~bb.occupiedSquares;
}

// parse a move according to the CURRENT board state
Move Board::parseMove(std::string lan) {
    std::array<std::string, 8> ranks = {"a", "b", "c", "d", "e", "f", "g", "h"};
    std::stringstream ss;
    unsigned int move = 0;
    unsigned int flags = 0;
    unsigned int index = 1;
    bool capture = false;
    bool pawnMove = false;
    bool castling = false;

    /// check for castling
    if (lan == "e1g1") { // white castles on kingside
        // set origin and dest
        move |= (E1 << 6);
        move |= G1;
        // set flags
        flags |= 0b0010;
        castling = true;
    } else if (lan == "e1c1") { // white castles on queenside
        // set origin and dest
        move |= (E1 << 6);
        move |= C1;
        // set flags
        flags |= 0b0011;
        castling = true;
    } else if (lan == "e8g8") { // black castles on kingside
        // set origin and dest
        move |= (E8 << 6);
        move |= G8;
        // set flags
        flags |= 0b0010;
        castling = true;
    } else if (lan == "e8c8") { // black castles queenside
        // set origin and dest
        move |= (E8 << 6);
        move |= C8;
        // set flags
        flags |= 0b0011;
        castling = true;
    }

    if (castling) {
        // set castling rights
        move |= (getLastState().castlingRights << 22);
        // set captured piece (none)
        move |= (NO_PIECE << 19);
        // set moved piece
        move |= (KING << 16);
        // set flags in move
        move |= (flags << 12);

        return Move(move);
    }


    char piece = Algorithms::asciiCharToLower(lan[0]); // piece moved, if not pawn

    /// set the moved piece type
    switch (piece) {
        case 'n' :
            move |= (KNIGHT) << 16;
            break;
        case 'b' :
            move |= (BISHOP) << 16;
            break;
        case 'r' :
            move |= (ROOK) << 16;
            break;
        case 'q' :
            move |= (QUEEN) << 16;
            break;
        case 'k' :
            move |= (KING) << 16;
            break;
        default: // pawn, bits already set to 0 so do nothing
            --index;
            pawnMove = true;
            break;
    }

    /// set the origin square
    char originFile = Algorithms::asciiCharToLower(lan[index]);
    char originRank = Algorithms::asciiCharToLower(lan[index + 1]);
    ESquare originSquare = getSquare(originFile, originRank);
    move |= (originSquare << 6);

    index += 2;

    /// check for capture and set capture flag (0b111 = no cap)
    if (Algorithms::asciiCharToLower(lan[index]) == 'x') {
        flags |= 0b0100; // set capture flag to true
        capture = true;
        ++index;
    }

    /// set the destination square
    char destFile = Algorithms::asciiCharToLower(lan[index]);
    char destRank = Algorithms::asciiCharToLower(lan[index + 1]);
    ESquare destSquare = getSquare(destFile, destRank);
    move |= destSquare;

    index += 2;

    /// set the captured piece field
    // if a piece was captured, find its type from the board state
    if (capture && !pawnMove) { // no possibility of en passant
        PieceType capturedPieceType = getPieceType(bb.squares[destSquare]);
        move |= (capturedPieceType << 19);
    } else if (capture && pawnMove) { // possibility of en passant
        if (destSquare == getLastState().enPassantSquare) { // en passant capture
            flags |= 0b0101; // set EP capture flag
        } else { // normal pawn capture
            PieceType capturedPieceType = getPieceType(bb.squares[destSquare]);
            move |= (capturedPieceType << 19);
        }
    } else { // set to 0b110 for no piece captured
        move |= (0b110 << 19);
    }

    /// check for promotion and set flags
    if (lan.length() > index) {
        unsigned int promotedTo;
        switch (Algorithms::asciiCharToLower(lan[index])) {
            case 'q':
                flags |= (0b1011);
                break;
            case 'r':
                flags |= (0b1010);
                break;
            case 'b':
                flags |= (0b1001);
                break;
            case 'n':
                flags |= (0b1000);
                break;
        }

        if (capture) { // capture promo
            flags |= (0b0100);
        }
    }

    /// double pawn push
    if (pawnMove && (abs(destSquare - originSquare) == 16)) {
        flags |= 0b0001;
    }

    /// set the flags
    move |= (flags << 12);

    /// set castling rights
    move |= (getLastState().castlingRights << 22);

    return Move(move);
}

// make a move
void Board::makeMove(Move move) {

}

// unmake a move
void Board::unmakeMove() {

}

// TODO: write this
ESquare Board::getSquare(char file, char rank) {
    std::string files = "abcdefgh";
    std::string ranks = "12345678";

    return (ESquare) (8 * ranks.find(rank) + files.find(file));
}

// initialize the BoardStateHistory with the given castling rights and en passant square
void BoardStateHistory::initialize(unsigned int c, ESquare sq) {
    BoardState state;
    state.enPassantSquare = sq;
    state.castlingRights = c;
    stateList.push_back(state);
}




#include <iostream>
#include <cstring>
#include <functional>
#include "Board.h"
#include "Algorithms.h"

Board::Board() {
    boardHistory = new BoardStateHistory(); // initialize pointer to BoardStateHistory
    movegen = new MoveGen(this);
}

Board::~Board() {

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

// set the board to the position specified by the given FEN
int Board::setFEN(std::string FEN) {
    unsigned int i, j, castle;
    ESquare sq;
    char letter;
    unsigned int file, rank;
    std::vector<std::string> strList;
    Algorithms::split(strList, FEN, " ");

    // empty the board squares
    for (sq = A1; sq <= H8; sq++) bb.squares[sq] = EMPTY;
    // read the board - translate each loop index into a square
    i = 0; // curr pos in fen string
    file = 0;
    rank = 7;
    while (i < strList[0].length()) {
        letter = strList[0].at(i);
        i++;

        sq = (ESquare) (rank*8 + file);
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
                rank--;
                file = -1;
                break;
            case '1' :
                break;
            case '2' :
                file++;
                break;
            case '3' :
                file+=2;
                break;
            case '4' :
                file+= 3;
                break;
            case '5' :
                file+= 4;
                break;
            case '6' :
                file+= 5;
                break;
            case '7' :
                file+= 6;
                break;
            case '8' :
                file+= 7;
                break;
            default:
                return -1;
        }
        file++;
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
    } else {
        castle = 0b1111;
    }

    // read en passant and save it into "sq" Default := None (ER)
    sq = ER;
    if ((strList.size() >= 4) && (strList[3].length() >= 2)) {
        if ((strList[3].at(0) >= 'a') && (strList[3].at(0) <= 'h') &&
            ((strList[3].at(1) == '3') || (strList[3].at(1) == '6'))) {
            file = strList[3].at(0) - 96; // ASCII 'a' = 97
            rank = strList[3].at(1) - 48; // ASCII '1' = 49
            sq = (ESquare) ((rank - 1) * 8 + file - 1);
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

// parse a move according to the CURRENT board state
Move Board::parseMove(std::string lan) {
    unsigned int move = 0;
    unsigned int flags = 0;
    int index = 0;


    /// check for castling
    bool castling = false;
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

    /// set the origin square
    char originFile = Algorithms::asciiCharToLower(lan[index]);
    char originRank = Algorithms::asciiCharToLower(lan[index + 1]);
    ESquare originSquare = getSquare(originFile, originRank);
    move |= (originSquare << 6);
    index += 2;

    /// check for capture and set capture flag
    bool capture = false;
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

    /// set the moved piece field
    PieceType pieceMoved = getPieceType(bb.squares[originSquare]); // piece moved
    move |= (pieceMoved) << 16;

    bool pawnMove = false;
    if (pieceMoved == PAWN) {
        pawnMove = true;
    }

    /// set the captured piece field
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

// make a move, assumes the move is valid
// TODO: state inCheck, repetitions, hash, etc
void Board::makeMove(Move move) {
    EColor otherSide = (sideToMove == WHITE) ? BLACK : WHITE;
    ESquare from = move.getOrigin();
    ESquare to = move.getDest();
    BoardState oldState = getLastState();
    BoardState newState;

    // move the piece on the board
    EPiece movedPiece = bb.squares[from];
    clearSquare(from, movedPiece, sideToMove);
    setSquare(to, movedPiece, sideToMove);

    if(move.isCapture()) {
        if (move.isEnPassant()) {
            if (sideToMove == WHITE) {
                bb.squares[to - 8] = EMPTY;
                clear_bit(bb.pcs[B_PAWN], (to - 8));
            } else {
                bb.squares[to + 8] = EMPTY;
                clear_bit(bb.pcs[B_PAWN], (to + 8));
            }
        } else {
            clearSquare(to, getPiece(move.getCapturedPieceType(), otherSide), otherSide);
        }
    }

    // castling logic, only need to do rook b/c king handled above
    if (move.isQueenSideCastling()) {
        if (sideToMove == WHITE) {
            clearSquare(A1, W_ROOK, WHITE);
            setSquare(D1, W_ROOK, WHITE);
        } else {
            clearSquare(A8, B_ROOK, BLACK);
            setSquare(D8, B_ROOK, BLACK);
        }
    } else if (move.isKingSideCastling()) {
        if (sideToMove == WHITE) {
            clearSquare(H1, W_ROOK, WHITE);
            setSquare(F1, W_ROOK, WHITE);
        } else {
            clearSquare(H1, B_ROOK, BLACK);
            setSquare(F1, B_ROOK, BLACK);
        }
    }

    // if the move is a promotion, promote it...
    if (move.isPromotion()) {
        EPiece promotionPiece = (EPiece) ((sideToMove == WHITE) ?
                                          (move.getPromotedPieceType() + 1) : (move.getPromotedPieceType() + 7));
        bb.squares[to] = promotionPiece;
        clearSquare(to, movedPiece, sideToMove);
        setSquare(to, promotionPiece, sideToMove);
    }

    // if the move is a double pawn push, set the en passant square
    if (move.isDoublePawnPush()) {
        if (sideToMove == WHITE) {
            newState.enPassantSquare = (ESquare) (to - 8);
        } else {
            newState.enPassantSquare = (ESquare) (to + 8);
        }
    } else {
        newState.enPassantSquare = ER;
    }

    // get new castling rights
    unsigned int castle = move.getPreviousCastlingRights();
    if (move.isCastling()) {
        if (sideToMove == WHITE) {
            castle &= 0b0011;
        } else {
            castle &= 0b1100;
        }
    }

    // update board
    sideToMove = otherSide;
    ++currentPly;

    newState.hash = 0; // TODO hashing function
    newState.lastTriggerEvent = ((move.getPieceType() == PAWN) || move.isCapture())
                                ? currentPly : oldState.lastTriggerEvent;
    newState.castlingRights = castle;
    newState.move = move;
    newState.inCheck = movegen->inCheck(sideToMove);
    // answer: probably something with move generation and attack tables and stuff, definitely a later problem
    // ideally this would be very fast
    newState.repetitions = oldState.repetitions; // also a todo but low priority

    boardHistory->addState(newState);
}

// unmake a move
void Board::unmakeMove() {
    if (getStateCount() < 2) return; // there is no state to go back to

    BoardState lastState = popBoardState();
    EColor otherSide = (sideToMove == BLACK) ? WHITE : BLACK;

    // reverse to and from
    ESquare to = lastState.move.getOrigin();
    ESquare from = lastState.move.getDest();

    // move the piece on the board
    EPiece movedPiece = bb.squares[from];
    bb.squares[from] = EMPTY;
    bb.squares[to] = movedPiece;

    // update bitboard
    clearSquare(from, movedPiece, sideToMove);
    setSquare(to, movedPiece, sideToMove);

    if (lastState.move.isCapture()) {
        if (lastState.move.isEnPassant()) {
            EPiece captured = getPiece(lastState.move.getCapturedPieceType(), otherSide); // should always be pawn
            int64 sq = (otherSide == WHITE) ? to << 8 : to >> 8;
            setSquare(sq, captured, otherSide);
        } else {
            EPiece captured = getPiece(lastState.move.getCapturedPieceType(), otherSide);
            setSquare(from, captured, otherSide);
        }
    }


    // king is already set, so we just need to update rook + castling state
    if(lastState.move.isQueenSideCastling()) {
        if(otherSide == WHITE) { // white king side castle
            setSquare(A1, W_ROOK, WHITE);
            clearSquare(D1, W_ROOK, WHITE);
        } else {
            setSquare(A8, B_ROOK, BLACK);
            clearSquare(D8, B_ROOK, BLACK);
        }
    } else if (lastState.move.isKingSideCastling()) {
        if(otherSide == WHITE) { // white queen side castle
            setSquare(H1, W_ROOK, WHITE);
            clearSquare(F1, W_ROOK, WHITE);
        } else {
            setSquare(H1, B_ROOK, BLACK);
            clearSquare(F1, B_ROOK, BLACK);
        }
    }

    // if promoted
    if(lastState.move.isPromotion()) {
        clearSquare(to, movedPiece, sideToMove);
        setSquare(to, (sideToMove == WHITE) ? W_PAWN : B_PAWN, sideToMove);
    }

    // update the board
    sideToMove = otherSide;
    --currentPly;
}

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

void Board::clearSquare(int64 sq, EPiece piece, EColor side) {
    clear_bit(bb.pcs[piece], sq);
    clear_bit(bb.pcsOfColor[side], sq);
    clear_bit(bb.occupiedSquares, sq);
    set_bit(bb.emptySquares, sq);
}

void Board::setSquare(int64 sq, EPiece piece, EColor side) {
    set_bit(bb.pcs[piece], sq);
    set_bit(bb.pcsOfColor[side], sq);
    set_bit(bb.occupiedSquares, sq);
    clear_bit(bb.emptySquares, sq);
}



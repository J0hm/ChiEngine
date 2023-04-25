#include "MoveGen.h"
#include "Algorithms.h"

#define FORWARD(sq) ((board->sideToMove == WHITE) ? NORTH(sq) : SOUTH(sq))
#define BACKWARD(sq) ((board->sideToMove == WHITE) ? SOUTH(sq) : NORTH(sq))

#define RESERVE_SIZE 196

void MoveGen::calcKnightAttackBitboard(EColor side) {
    int64 bb = 0;
    EBitBoard knightOcc = board->bb.pcs[2 + 6 * side];

    while (knightOcc) {
        bb |= (knightAttackTable[SHIFTED_SQUARE[pop_LSB(knightOcc)]] & ~board->bb.pcsOfColor[side]);
    }

    knightAttackBitboard[side] = bb;
}

void MoveGen::calcBishopAttackBitboard(EColor side) {
    int64 bb = 0;
    EBitBoard bishopOcc = board->bb.pcs[3 + 6 * side];

    while (bishopOcc) {
        bb |= (magic->getBishopAttacks(pop_LSB(bishopOcc), board->bb.occupiedSquares)
               & ~board->bb.pcsOfColor[side]);
    }

    bishopAttackBitBoard[side] = bb;
}

void MoveGen::calcRookAttackBitboard(EColor side) {
    int64 bb = 0;
    EBitBoard rookOcc = board->bb.pcs[4 + 6 * side];

    while (rookOcc) {
        bb |= ((magic->getRookAttacks(pop_LSB(rookOcc),
                                      board->bb.occupiedSquares)
                & ~board->bb.pcsOfColor[side]));
    }

    rookAttackBitBoard[side] = bb;
}

void MoveGen::calcQueenAttackBitboard(EColor side) {
    int64 bb = 0;
    EBitBoard queenOcc = board->bb.pcs[5 + 6 * side];

    while (queenOcc) {
        bb |= (magic->getQueenAttacks(pop_LSB(queenOcc),
                                      board->bb.occupiedSquares)
               & ~board->bb.pcsOfColor[side]);
    }

    queenAttackBitBoard[side] = bb;
}

void MoveGen::calcPawnAttackBitboard(EColor side) {
    int64 bb = 0;
    int64 pawnOcc = board->bb.pcs[1 + 6 * side];

    while (pawnOcc) {
        int64 bbSquare = (1ULL << pop_LSB(pawnOcc));
        if (side == WHITE) {
            if ((NORTH(EAST(bbSquare)) & ~board->bb.pcsOfColor[side]) &&
                (bbSquare & ~0x0101010101010101)) {
                bb |= NORTH(EAST(bbSquare));
            }
            if ((NORTH(WEST(bbSquare)) & ~board->bb.pcsOfColor[side]) &&
                (bbSquare & ~0x8080808080808080)) {
                bb |= NORTH(WEST(bbSquare));
            }
        } else {
            if ((SOUTH(EAST(bbSquare)) & ~board->bb.pcsOfColor[side]) &&
                (bbSquare & ~0x0101010101010101)) {
                bb |= SOUTH(EAST(bbSquare));
            }
            if ((SOUTH(WEST(bbSquare)) & ~board->bb.pcsOfColor[side]) &&
                (bbSquare & ~0x8080808080808080)) {
                bb |= SOUTH(WEST(bbSquare));
            }
        }
    }

    pawnAttackBitBoard[side] = bb;
}

void MoveGen::calcKingAttackBitboard(EColor side) {
    int64 square = board->bb.pcs[6 + 6 * side];

    int64 bb = (((square << 1) | (square >> 7) | (square << 9)) & ~0x0101010101010101) |
               (((square >> 9) | (square << 7) | (square >> 1)) & ~0x8080808080808080) |
               ((square << 8) & ~0xFF) |
               ((square >> 8) & ~0xFF00000000000000);

    bb &= ~board->bb.pcsOfColor[side]; // cant attack own pieces

    kingAttackBitboard[side] = bb;
}

void MoveGen::calcAllAttackBitboard(EColor side) {
    int64 bb = 0;
    calcPawnAttackBitboard(side);
    calcKnightAttackBitboard(side);
    calcBishopAttackBitboard(side);
    calcRookAttackBitboard(side);
    calcQueenAttackBitboard(side);
    calcKingAttackBitboard(side);

    bb |= pawnAttackBitBoard[side] |
          knightAttackBitboard[side] |
          bishopAttackBitBoard[side] |
          rookAttackBitBoard[side] |
          queenAttackBitBoard[side] |
          kingAttackBitboard[side];

    allAttackBitBoard[side] = bb;
}

void MoveGen::initKnightAttackTable() {
    int64 bbSquare;
    int64 attacks;
    for (int square = 0; square < 64; square++) {
        bbSquare = BB_SQUARES[square];
        attacks = (((bbSquare >> 6) | (bbSquare << 10)) & ~0x303030303030303) |
                  (((bbSquare >> 10) | (bbSquare << 6)) & ~0xC0C0C0C0C0C0C0C0) |
                  (((bbSquare >> 15) | (bbSquare << 17)) & ~0x101010101010101) |
                  (((bbSquare >> 17) | (bbSquare << 15)) & ~0x8080808080808080);
        knightAttackTable[square] = attacks;
    }
}

bool MoveGen::inCheck(EColor side) {
    int64 king = board->bb.pcs[6 + 6 * side];
    calcAllAttackBitboard((side == WHITE) ? BLACK : WHITE);

    return king & allAttackBitBoard[(side == WHITE) ? BLACK : WHITE];
}

bool MoveGen::isLegal(Move m) {
    if (board->getLastState().inCheck) { // if we are in check, only moves that resolve check are legal
        return resolvesCheck(m) && !doesCheck(m, board->sideToMove);
    } else {
        return !doesCheck(m, board->sideToMove);
    }
}

bool MoveGen::doesCheck(Move m, EColor toColor) {
    bool doesCheck;

    board->makeMove(m);
    doesCheck = inCheck(toColor);
    board->unmakeMove();

    return doesCheck;
}

bool MoveGen::resolvesCheck(Move m) {
    bool resolves;
    EColor side = board->sideToMove;

    board->makeMove(m);
    resolves = !inCheck(side);
    board->unmakeMove();

    return resolves;
}

std::vector<Move> MoveGen::getPawnMoves() {
    std::vector<Move> moves;
    int64 pawnOcc = board->bb.pcs[1 + 6 * board->sideToMove];
    EColor otherSide = (board->sideToMove == WHITE ? BLACK : WHITE);
    unsigned int castle = board->getLastState().castlingRights;

    while (pawnOcc) {
        int square = SHIFTED_SQUARE[pop_LSB(pawnOcc)]; // [0, 63]
        int64 bbSquare = BB_SQUARES[square]; // bitboard representation of the square

        // pawn on starting rank
        if ((bbSquare & 0xFF00) && (board->sideToMove == WHITE)) {
            if ((board->bb.emptySquares & FORWARD(bbSquare)) && (board->bb.emptySquares & (bbSquare << 16)))
                moves.emplace_back(square + 16, square, 0b000, 0b110, 0b0001, castle, 0);
        } else if ((bbSquare & 0xFF000000000000) && (board->sideToMove == BLACK)) {
            if ((board->bb.emptySquares & FORWARD(bbSquare)) && (board->bb.emptySquares & (bbSquare >> 16)))
                moves.emplace_back(square - 16, square, 0b000, 0b110, 0b0001, castle, 0);
        }

        // pawn on rank 2/7 (must promote)
        if ((bbSquare & 0xFF000000000000) && (board->sideToMove == WHITE)) {
            if (NORTH(bbSquare) & ~board->bb.occupiedSquares) { // simple promotion case
                moves.emplace_back(square + 8, square, 0b000, 0b110, 0b1000, castle, 20);
                moves.emplace_back(square + 8, square, 0b000, 0b110, 0b1001, castle, 30);
                moves.emplace_back(square + 8, square, 0b000, 0b110, 0b1010, castle, 50);
                moves.emplace_back(square + 8, square, 0b000, 0b110, 0b1011, castle, 100);
            }

            if (NORTHWEST(bbSquare) & board->bb.pcsOfColor[BLACK]) {
                int captured = getPieceType(board->bb.squares[square + 7]);
                moves.emplace_back(square + 7, square, 0b000, captured, 0b1100, castle, 35+10*captured);
                moves.emplace_back(square + 7, square, 0b000, captured, 0b1101, castle, 45+10*captured);
                moves.emplace_back(square + 7, square, 0b000, captured, 0b1110, castle, 65+10*captured);
                moves.emplace_back(square + 7, square, 0b000, captured, 0b1111, castle, 115+10*captured);
            }

            if (NORTHEAST(bbSquare) & board->bb.pcsOfColor[BLACK]) {
                int captured = getPieceType(board->bb.squares[square + 9]);
                moves.emplace_back(square + 9, square, 0b000, captured, 0b1100, castle, 35+10*captured);
                moves.emplace_back(square + 9, square, 0b000, captured, 0b1101, castle, 45+10*captured);
                moves.emplace_back(square + 9, square, 0b000, captured, 0b1110, castle, 65+10*captured);
                moves.emplace_back(square + 9, square, 0b000, captured, 0b1111, castle, 115+10*captured);
            }
        } else if ((bbSquare & 0xFF00) && (board->sideToMove == BLACK)) {
            if (SOUTH(bbSquare) & ~board->bb.occupiedSquares) { // simple promotion case
                moves.emplace_back(square - 8, square, 0b000, 0b110, 0b1000, castle, 20);
                moves.emplace_back(square - 8, square, 0b000, 0b110, 0b1001, castle, 30);
                moves.emplace_back(square - 8, square, 0b000, 0b110, 0b1010, castle, 50);
                moves.emplace_back(square - 8, square, 0b000, 0b110, 0b1011, castle, 100);
            }

            if (SOUTHWEST(bbSquare) & board->bb.pcsOfColor[WHITE]) {
                int captured = getPieceType(board->bb.squares[square - 9]);
                moves.emplace_back(square - 9, square, 0b000, captured, 0b1100, castle, 35+10*captured);
                moves.emplace_back(square - 9, square, 0b000, captured, 0b1101, castle, 45+10*captured);
                moves.emplace_back(square - 9, square, 0b000, captured, 0b1110, castle, 65+10*captured);
                moves.emplace_back(square - 9, square, 0b000, captured, 0b1111, castle, 115+10*captured);
            }

            if (SOUTHEAST(bbSquare) & board->bb.pcsOfColor[WHITE]) {
                int captured = getPieceType(board->bb.squares[square - 7]);
                moves.emplace_back(square - 7, square, 0b000, captured, 0b1100, castle, 35+10*captured);
                moves.emplace_back(square - 7, square, 0b000, captured, 0b1101, castle, 45+10*captured);
                moves.emplace_back(square - 7, square, 0b000, captured, 0b1110, castle, 65+10*captured);
                moves.emplace_back(square - 7, square, 0b000, captured, 0b1111, castle, 115+10*captured);
            }
        } else {
            // normal forward
            if (FORWARD(bbSquare) & board->bb.emptySquares) {
                int toSquare = (otherSide == BLACK) ? square + 8 : square - 8;
                moves.emplace_back(toSquare, square, 0b000, 0b110, 0, castle, 0);
            }
            // forward east and not on H file capture
            if ((FORWARD(EAST(bbSquare)) & board->bb.pcsOfColor[otherSide]) &&
                (bbSquare & ~0x0101010101010101)) {
                int toSquare = SHIFTED_SQUARE[get_LSB(FORWARD(EAST(bbSquare)))];
                PieceType captured = getPieceType(board->bb.squares[toSquare]);
                moves.emplace_back(toSquare, square, 0b000, captured, 0b0100, castle, 15+10*captured);
            }
            // forward west and not on A file capture
            if ((FORWARD(WEST(bbSquare)) & board->bb.pcsOfColor[otherSide]) &&
                (bbSquare & ~0x8080808080808080)) {
                int toSquare = SHIFTED_SQUARE[get_LSB(FORWARD(WEST(bbSquare)))];
                PieceType captured = getPieceType(board->bb.squares[toSquare]);
                moves.emplace_back(toSquare, square, 0b000, captured, 0b0100, castle, 15+10*captured);
            }
        }

        // en passant
        if (board->sideToMove == WHITE) {
            unsigned int epSquare = board->getLastState().enPassantSquare;
            if ((bbSquare & 0xFF00000000) && (square + 7 == epSquare) && ((bbSquare << 9) & board->bb.emptySquares)) {
                moves.emplace_back(square + 7, square, 0b000, 0b000, 0b0101, castle, 15);
            } else if ((bbSquare & 0xFF00000000) && (square + 9 == epSquare) &&
                       ((bbSquare << 7) & board->bb.emptySquares)) {
                moves.emplace_back(square + 9, square, 0b000, 0b000, 0b0101, castle, 15);
            }
        } else {
            unsigned int epSquare = board->getLastState().enPassantSquare;
            if ((bbSquare & 0xFF000000) && (square - 7 == epSquare) && ((bbSquare >> 9) & board->bb.emptySquares)) {
                moves.emplace_back(square - 7, square, 0b000, 0b000, 0b0101, castle, 15);
            } else if ((bbSquare & 0xFF000000) && (square - 9 == epSquare) &&
                       ((bbSquare >> 7) & board->bb.emptySquares)) {
                moves.emplace_back(square - 9, square, 0b000, 0b000, 0b0101, castle, 15);
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGen::getKnightMoves() {
    std::vector<Move> moves;
    int64 knightOcc = board->bb.pcs[2 + 6 * board->sideToMove];
    EColor otherSide = (board->sideToMove == WHITE ? BLACK : WHITE);
    unsigned int castle = board->getLastState().castlingRights;

    while (knightOcc) {
        unsigned int from = SHIFTED_SQUARE[pop_LSB(knightOcc)]; // [0, 63]
        int64 attacks = knightAttackTable[from];

        while (attacks) {
            unsigned int to = SHIFTED_SQUARE[pop_LSB(attacks)];
            int64 toBBSquare = BB_SQUARES[to];

            if (toBBSquare & board->bb.pcsOfColor[otherSide]) { // capture
                PieceType captured = getPieceType(board->bb.squares[to]);
                moves.emplace_back(to, from, 0b001, captured, 0b0100, castle, 14+10*captured);
            } else if (toBBSquare & board->bb.emptySquares) {
                moves.emplace_back(to, from, 0b001, 0b110, 0b000, castle, 0);
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGen::getBishopMoves() {
    std::vector<Move> moves;
    int64 bishopOcc = board->bb.pcs[3 + 6 * board->sideToMove];
    EColor otherSide = (board->sideToMove == WHITE ? BLACK : WHITE);
    unsigned int castle = board->getLastState().castlingRights;

    while (bishopOcc) {
        int from = SHIFTED_SQUARE[get_LSB(bishopOcc)];
        int64 attacks = (magic->getBishopAttacks(pop_LSB(bishopOcc), board->bb.occupiedSquares)
                         & ~board->bb.pcsOfColor[board->sideToMove]);

        while (attacks) {
            int to = SHIFTED_SQUARE[pop_LSB(attacks)];
            int64 toBBSquare = BB_SQUARES[to];

            if (toBBSquare & board->bb.pcsOfColor[otherSide]) { // capture
                PieceType captured = getPieceType(board->bb.squares[to]);
                moves.emplace_back(to, from, 0b010, captured, 0b0100, castle, 13+10*captured);
            } else if (toBBSquare & board->bb.emptySquares) { // no capture
                moves.emplace_back(to, from, 0b010, 0b110, 0b0000, castle, 0);
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGen::getRookMoves() {
    std::vector<Move> moves;
    int64 rookOcc = board->bb.pcs[4 + 6 * board->sideToMove];
    EColor otherSide = (board->sideToMove == WHITE ? BLACK : WHITE);
    unsigned int castle = board->getLastState().castlingRights;

    while (rookOcc) {
        int from = SHIFTED_SQUARE[get_LSB(rookOcc)];
        int64 attacks = (magic->getRookAttacks(pop_LSB(rookOcc), board->bb.occupiedSquares)
                         & ~board->bb.pcsOfColor[board->sideToMove]);
        while (attacks) {
            int to = SHIFTED_SQUARE[pop_LSB(attacks)];
            int64 toBBSquare = BB_SQUARES[to];

            if (toBBSquare & board->bb.pcsOfColor[otherSide]) { // capture
                PieceType captured = getPieceType(board->bb.squares[to]);
                moves.emplace_back(to, from, 0b011, captured, 0b0100, castle, 12+10*captured);
            } else if (toBBSquare & board->bb.emptySquares) { // no capture
                moves.emplace_back(to, from, 0b011, 0b110, 0b0000, castle, 0);
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGen::getQueenMoves() {
    std::vector<Move> moves;
    int64 queenOcc = board->bb.pcs[5 + 6 * board->sideToMove];
    EColor otherSide = (board->sideToMove == WHITE ? BLACK : WHITE);
    unsigned int castle = board->getLastState().castlingRights;

    while (queenOcc) {
        int from = SHIFTED_SQUARE[get_LSB(queenOcc)];
        int64 attacks = (magic->getQueenAttacks(pop_LSB(queenOcc), board->bb.occupiedSquares)
                         & ~board->bb.pcsOfColor[board->sideToMove]);

        while (attacks) {
            int to = SHIFTED_SQUARE[pop_LSB(attacks)];
            int64 toBBSquare = BB_SQUARES[to];

            if (toBBSquare & board->bb.pcsOfColor[otherSide]) { // capture
                PieceType captured = getPieceType(board->bb.squares[to]);
                moves.emplace_back(to, from, 0b100, captured, 0b0100, castle, 11+10*captured);
            } else if (toBBSquare & board->bb.emptySquares) { // no capture
                moves.emplace_back(to, from, 0b100, 0b110, 0b0000, castle, 0);
            }
        }
    }

    return moves;
}

// TODO abstract this... while loop for most of these can be abstracted, maybe even entire method
std::vector<Move> MoveGen::getKingMoves() {
    std::vector<Move> moves;
    int64 fromBBSquare = board->bb.pcs[6 + 6 * board->sideToMove];
    int from = SHIFTED_SQUARE[get_LSB(fromBBSquare)];
    EColor otherSide = (board->sideToMove == WHITE ? BLACK : WHITE);
    unsigned int castle = board->getLastState().castlingRights;

    calcKingAttackBitboard(board->sideToMove);
    int64 attacks = kingAttackBitboard[board->sideToMove];

    // normal attacks
    while (attacks) {
        int to = SHIFTED_SQUARE[pop_LSB(attacks)];
        int64 toBBSquare = BB_SQUARES[to];

        if (toBBSquare & board->bb.pcsOfColor[otherSide]) { // capture
            PieceType captured = getPieceType(board->bb.squares[to]);
            moves.emplace_back(to, from, 0b101, captured, 0b0100, castle, 10+10*captured);
        } else if (toBBSquare & board->bb.emptySquares) { // no capture
            moves.emplace_back(to, from, 101, 0b110, 0b0000, castle, 0);
        }
    }

    // castling
    if (board->sideToMove == WHITE) {
        calcAllAttackBitboard(BLACK);
        if ((castle & 0b1000) &&
            ((board->bb.occupiedSquares & 0x70) == 0) &&
            !(allAttackBitBoard[BLACK] & 0x38)) {
            // white castles queen side, e1c1 if b1c1d1 empty, not under attack by white
            moves.emplace_back(C1, E1, 0b101, 0b110, 0b0011, castle, 2);
        }
        if ((castle & 0b0100) &&
            ((board->bb.occupiedSquares & 0x6) == 0) &&
            !(allAttackBitBoard[BLACK] & 0xE)) { // white castles king side, e1g1 if f1g1 empty
            moves.emplace_back(G1, E1, 0b101, 0b110, 0b0010, castle, 2);
        }
    } else {
        calcAllAttackBitboard(WHITE);
        if ((castle & 0b0010) &&
            ((board->bb.occupiedSquares & 0x7000000000000000) == 0) &&
            !(allAttackBitBoard[WHITE] & 0x3800000000000000)) { // black castles queen side, e8c8 if b8c8d8 empty
            moves.emplace_back(C8, E8, 0b101, 0b110, 0b0011, castle, 2);
        }
        if ((castle & 0b0001) &&
            ((board->bb.occupiedSquares & 0x0600000000000000) ==
             0) &&
            !(allAttackBitBoard[WHITE] & 0x0E00000000000000)) { // white castles king side, e8g8 if f8g8 empty
            moves.emplace_back(G8, E8, 0b101, 0b110, 0b0010, castle, 2);
        }
    }

    return moves;
}

// TODO reserve vector size
std::vector<Move> MoveGen::getLegalMoves() {
    std::vector<Move> moves;
    moves.reserve(RESERVE_SIZE);

    std::vector<Move> pawn = getPawnMoves();
    std::vector<Move> knight = getKnightMoves();
    std::vector<Move> bishop = getBishopMoves();
    std::vector<Move> rook = getRookMoves();
    std::vector<Move> queen = getQueenMoves();
    std::vector<Move> king = getKingMoves();

    // only copy moves if they are legal
    std::copy_if(pawn.begin(), pawn.end(), std::back_inserter(moves), [this](Move m) { return isLegal(m); });
    std::copy_if(knight.begin(), knight.end(), std::back_inserter(moves), [this](Move m) { return isLegal(m); });
    std::copy_if(bishop.begin(), bishop.end(), std::back_inserter(moves), [this](Move m) { return isLegal(m); });
    std::copy_if(rook.begin(), rook.end(), std::back_inserter(moves), [this](Move m) { return isLegal(m); });
    std::copy_if(queen.begin(), queen.end(), std::back_inserter(moves), [this](Move m) { return isLegal(m); });
    std::copy_if(king.begin(), king.end(), std::back_inserter(moves), [this](Move m) { return isLegal(m); });

    // largest move order rating first, so we can use an iterated for loop and get the "best" moves first
    std::sort(moves.begin(), moves.end(), std::greater <>());

    return moves;
}
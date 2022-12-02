#include "MoveGen.h"

#define FORWARD(sq) ((board->sideToMove == WHITE) ? NORTH(sq) : SOUTH(sq))
#define BACKWARD(sq) ((board->sideToMove == WHITE) ? SOUTH(sq) : NORTH(sq))

void MoveGen::calcBishopAttackBitboard(EColor side) {
    int64 bb = 0;
    EBitBoard bishopOcc = board->bb.pcs[3 + 6 * side];

    while (bishopOcc) {
        bb |= magic->getBishopAttacks((ESquare) pop_LSB(bishopOcc),
                                      board->bb.occupiedSquares & !board->bb.pcsOfColor[side]);
    }

    bishopAttackBitBoard[side] = bb;
}

void MoveGen::calcRookAttackBitboard(EColor side) {
    int64 bb = 0;
    EBitBoard rookOcc = board->bb.pcs[4 + 6 * side];

    while (rookOcc) {
        bb |= magic->getRookAttacks((ESquare) pop_LSB(rookOcc),
                                    board->bb.occupiedSquares & !board->bb.pcsOfColor[side]);
    }

    rookAttackBitBoard[side] = bb;
}

void MoveGen::calcQueenAttackBitboard(EColor side) {
    int64 bb = 0;
    EBitBoard queenOcc = board->bb.pcs[5 + 6 * side];

    while (queenOcc) {
        bb |= magic->getQueenAttacks((ESquare) pop_LSB(queenOcc),
                                     board->bb.occupiedSquares & !board->bb.pcsOfColor[side]);
    }

    rookAttackBitBoard[side] = bb;
}

void MoveGen::calcPawnAttackBitboard(EColor side) {
    int64 bb = 0;
    EBitBoard pawnOcc = board->bb.pcs[1 + 6 * side];

    while (pawnOcc) {
        int square = pop_LSB(pawnOcc);
        if (side == WHITE && square < 55) {
            bb |= square << 7;
            bb |= square << 9;
        } else if (side == BLACK && square > 7) {
            bb |= square >> 7;
            bb |= square >> 9;
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

    kingAttackBitboard[side] = bb;
}

void MoveGen::calcAllAttackBitboard(EColor side) {
    int64 bb = 0;
    calcPawnAttackBitboard(side);
    calcBishopAttackBitboard(side);
    calcRookAttackBitboard(side);
    calcQueenAttackBitboard(side);
    calcKingAttackBitboard(side);

    bb |= pawnAttackBitBoard[side] |
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
    calcAllAttackBitboard(side);
    return king & allAttackBitBoard[(side == WHITE) ? BLACK : WHITE];
}

bool MoveGen::isLegal(Move m) {
    if (board->getLastState().inCheck) { // if we are in check, only moves that resolve check are legal
        return resolvesCheck(m) && !doesCheck(m, board->sideToMove);;
    }
    return !doesCheck(m, board->sideToMove);
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
    // TODO
    // 1 forward, 2 forward, capture, en passant, promotion
    std::vector<Move> moves;
    EBitBoard pawnOcc = board->bb.pcs[1 + 6 * board->sideToMove];
    EColor otherSide = (board->sideToMove == WHITE ? BLACK : WHITE);
    unsigned int castle = board->getLastState().castlingRights;

    while (pawnOcc) {
        int square = pop_LSB(pawnOcc); // [0, 63]
        int64 bbSquare = BB_SQUARES[square]; // bitboard representation of the square

        // empty square in front of pawn
        if (FORWARD(bbSquare) & ~board->bb.occupiedSquares) {
            int toSquare = (otherSide == BLACK) ? square + 8 : square - 8;
            moves.emplace_back(toSquare, square, 0b000, 0b110, 0, castle);
        }

        // pawn on starting rank
        if ((bbSquare & 0xFF00) && (board->sideToMove == WHITE)) {
            if ((board->bb.emptySquares & FORWARD(bbSquare)) && (board->bb.emptySquares & (bbSquare << 16)))
                moves.emplace_back(square - 16, square, 0b000, 0b110, 0b0001, castle);
        } else if ((bbSquare & 0xFF00000000000) && (board->sideToMove == BLACK)) {
            if ((board->bb.emptySquares & FORWARD(bbSquare)) && (board->bb.emptySquares & (bbSquare >> 16)))
                moves.emplace_back(square + 16, square, 0b000, 0b110, 0b0001, castle);
        }

        // pawn on rank 2/7 (can promote)
        if ((bbSquare & 0xFF000000000000) && (board->sideToMove == WHITE)) {
            if(NORTH(bbSquare) & ~board->bb.occupiedSquares) { // simple promotion case
                moves.emplace_back(square + 8, square, 0b000, 0b110, 0b1000, castle);
                moves.emplace_back(square + 8, square, 0b000, 0b110, 0b1001, castle);
                moves.emplace_back(square + 8, square, 0b000, 0b110, 0b1010, castle);
                moves.emplace_back(square + 8, square, 0b000, 0b110, 0b1011, castle);
            }

            if(NORTHEAST(bbSquare) & board->bb.pcsOfColor[BLACK]) {
                int captured = getPieceType(board->bb.squares[square + 7]);
                moves.emplace_back(square + 7, square, 0b000, captured, 0b1100, castle);
                moves.emplace_back(square + 7, square, 0b000, captured, 0b1101, castle);
                moves.emplace_back(square + 7, square, 0b000, captured, 0b1110, castle);
                moves.emplace_back(square + 7, square, 0b000, captured, 0b1111, castle);
            }

            if(NORTHWEST(bbSquare) & board->bb.pcsOfColor[BLACK]) {
                int captured = getPieceType(board->bb.squares[square + 9]);
                moves.emplace_back(square + 9, square, 0b000, captured, 0b1100, castle);
                moves.emplace_back(square + 9, square, 0b000, captured, 0b1101, castle);
                moves.emplace_back(square + 9, square, 0b000, captured, 0b1110, castle);
                moves.emplace_back(square + 9, square, 0b000, captured, 0b1111, castle);
            }
        } else if ((bbSquare & 0xFF00) && (board->sideToMove == BLACK)) {
            if(SOUTH(bbSquare) & ~board->bb.occupiedSquares) { // simple promotion case
                moves.emplace_back(square - 8, square, 0b000, 0b110, 0b1000, castle);
                moves.emplace_back(square - 8, square, 0b000, 0b110, 0b1001, castle);
                moves.emplace_back(square - 8, square, 0b000, 0b110, 0b1010, castle);
                moves.emplace_back(square - 8, square, 0b000, 0b110, 0b1011, castle);
            }

            if(SOUTHEAST(bbSquare) & board->bb.pcsOfColor[BLACK]) {
                int captured = getPieceType(board->bb.squares[square - 9]);
                moves.emplace_back(square - 9, square, 0b000, captured, 0b1100, castle);
                moves.emplace_back(square - 9, square, 0b000, captured, 0b1101, castle);
                moves.emplace_back(square - 9, square, 0b000, captured, 0b1110, castle);
                moves.emplace_back(square - 9, square, 0b000, captured, 0b1111, castle);
            }

            if(SOUTHWEST(bbSquare) & board->bb.pcsOfColor[BLACK]) {
                int captured = getPieceType(board->bb.squares[square - 7]);
                moves.emplace_back(square - 7, square, 0b000, captured, 0b1100, castle);
                moves.emplace_back(square - 7, square, 0b000, captured, 0b1101, castle);
                moves.emplace_back(square - 7, square, 0b000, captured, 0b1110, castle);
                moves.emplace_back(square - 7, square, 0b000, captured, 0b1111, castle);
            }
        }

        // en passant
        if(board->sideToMove == WHITE) {
            unsigned int epSquare = board->getLastState().enPassantSquare;
            if((square + 7 == epSquare) && ((bbSquare << 7) & board->bb.emptySquares)) {
                moves.emplace_back(square + 7, square, 0b000, 0b000, 0b0101, castle);
            } else if((square + 9 == epSquare) && ((bbSquare << 9) & board->bb.emptySquares)) {
                moves.emplace_back(square + 9, square, 0b000, 0b000, 0b0101, castle);
            }
        } else {
            unsigned int epSquare = board->getLastState().enPassantSquare;
            if((square - 7 == epSquare) && ((bbSquare >> 7) & board->bb.emptySquares)) {
                moves.emplace_back(square - 7, square, 0b000, 0b000, 0b0101, castle);
            } else if((square - 9 == epSquare) && ((bbSquare >> 9) & board->bb.emptySquares)) {
                moves.emplace_back(square - 9, square, 0b000, 0b000, 0b0101, castle);
            }
        }
    }

    return moves;
}

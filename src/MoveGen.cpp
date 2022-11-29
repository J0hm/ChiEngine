#include "MoveGen.h"

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

void MoveGen::calcAllAttackBitboard(EColor side) {
    int64 bb = 0;
    calcPawnAttackBitboard(side);
    calcBishopAttackBitboard(side);
    calcRookAttackBitboard(side);
    calcQueenAttackBitboard(side);

    bb |= pawnAttackBitBoard[side] | bishopAttackBitBoard[side] | rookAttackBitBoard[side] | queenAttackBitBoard[side];

    allAttackBitBoard[side] = bb;
}

void MoveGen::initKnightAttackTable() {
    for (int square = 0; square < 64; square++) {
        int64 bbSquare = BB_SQUARES[square];
        int64 attacks = (((bbSquare >> 6) | (bbSquare << 10)) & ~0x303030303030303) |
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
    if(board->getLastState().inCheck) { // if we are in check, only moves that resolve check are legal
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

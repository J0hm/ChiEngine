#include "ZobristHasher.h"

int64 ZobristHasher::hashBitBoard(BoardBB bb, EColor sideToMove, unsigned int castling, ESquare epSquare) {
    int64 hash = 0;

    for(int piece = 1; piece <= 12; piece++) { // iterate over each piece
        int64 pieceBB = bb.pcs[piece];
        while(pieceBB) {
            int sq = SHIFTED_SQUARE[pop_LSB(pieceBB)];
            hash ^= pieceKey[piece-1][sq];
        }
    }

    if(epSquare != ER) {
        int epFile = epSquare % 8;
        hash ^= enPassantFileKey[epFile];
    }

    if(sideToMove == BLACK) {
        hash ^= blackMoveKey;
    }

    hash ^= castlingKey[castling];

    return hash;
}

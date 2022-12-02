#ifndef CHIENGINE_ZOBRISTHASHER_H
#define CHIENGINE_ZOBRISTHASHER_H

#include <random>
#include <iostream>
#include "Types.h"

class ZobristHasher {
public:
    ZobristHasher() {
        rand.seed(0);
        initKeys();
    }

    int64 hashBitBoard(BoardBB bb, EColor sideToMove, unsigned int castling, ESquare epSquare);

private:
    int64 pieceKey[12][64]; // [EPiece-1][square]
    int64 castlingKey[16]; // base10 representation of 4 castling bits
    int64 enPassantFileKey[8];
    int64 blackMoveKey;

    std::mersenne_twister_engine<int64, 64, 312, 156, 31,
            0xb5026f5aa96619e9, 29,
            0x5555555555555555, 17,
            0x71d67fffeda60000, 37,
            0xfff7eee000000000, 43, 6364136223846793005> rand;

    void initKeys() {
        for(auto &p : pieceKey) {
            for(int64 &s : p) {
                s = rand.operator()();
            }
        }

        for(int64 &i : castlingKey) {
            i = rand.operator()();
        }

        for(int64 &i : enPassantFileKey) {
            i = rand.operator()();
        }

        blackMoveKey = rand.operator()();
    }


};


#endif //CHIENGINE_ZOBRISTHASHER_H

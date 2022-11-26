#include <cmath>
#include "MagicMoves.h"

int64 initOCCMagicMoves(const int *squares, const int numSquares, const int64 linocc) {
    int i;
    int64 ret = 0;
    for (i = 0; i < numSquares; i++)
        if (linocc & (((int64) (1)) << i)) ret |= (((int64) (1)) << squares[i]);
    return ret;
}

int64 initRookMagicMoves(const int square, const int64 occ) {
    int64 ret = 0;
    int64 bit;
    int64 rowbits = (((int64) 0xFF) << (8 * (square / 8)));

    bit = (((int64) (1)) << square);

    do {
        bit <<= 8;
        ret |= bit;
    } while (bit && !(bit & occ));

    bit = (((int64) (1)) << square);
    do {
        bit >>= 8;
        ret |= bit;
    } while (bit && !(bit & occ));

    bit = (((int64) (1)) << square);
    do {
        bit <<= 1;
        if (bit & rowbits) ret |= bit;
        else break;
    } while (!(bit & occ));

    bit = (((int64) (1)) << square);
    do {
        bit >>= 1;
        if (bit & rowbits) ret |= bit;
        else break;
    } while (!(bit & occ));

    return ret;
}

int64 initBishopMagicsMoves(const int square, const int64 occ) {
    int64 ret = 0;
    int64 bit;
    int64 bit2;
    int64 rowbits = (((int64) 0xFF) << (8 * (square / 8)));

    bit = (((int64) (1)) << square);
    bit2 = bit;
    do {
        bit <<= 8 - 1;
        bit2 >>= 1;
        if (bit2 & rowbits) ret |= bit;
        else break;
    } while (bit && !(bit & occ));

    bit = (((int64) (1)) << square);
    bit2 = bit;
    do {
        bit <<= 8 + 1;
        bit2 <<= 1;
        if (bit2 & rowbits) ret |= bit;
        else break;
    } while (bit && !(bit & occ));

    bit = (((int64) (1)) << square);
    bit2 = bit;
    do {
        bit >>= 8 - 1;
        bit2 <<= 1;
        if (bit2 & rowbits) ret |= bit;
        else break;
    } while (bit && !(bit & occ));

    bit = (((int64) (1)) << square);
    bit2 = bit;
    do {
        bit >>= 8 + 1;
        bit2 >>= 1;
        if (bit2 & rowbits) ret |= bit;
        else break;
    } while (bit && !(bit & occ));

    return ret;
}

void MagicMoves::initMagics() {
    int i;

    //for bitscans :
    int bitPos64DB[64] = {
            63, 0, 58, 1, 59, 47, 53, 2,
            60, 39, 48, 27, 54, 33, 42, 3,
            61, 51, 37, 40, 49, 18, 28, 20,
            55, 30, 34, 11, 43, 14, 22, 4,
            62, 57, 46, 52, 38, 26, 32, 41,
            50, 36, 17, 19, 29, 10, 13, 21,
            56, 45, 25, 31, 35, 16, 9, 12,
            44, 24, 15, 8, 23, 7, 6, 5};

    for (i = 0; i < 64; i++) {
        int squares[64];
        int numSquares = 0;
        int64 bMask = bishopMasks[i];
        while (bMask) {
            int64 bit = bMask & -bMask;
            squares[numSquares++] = bitPos64DB[(bit * 0x07EDD5E59A4E28C2) >> 58];
            bMask ^= bit;
        }
        for (bMask = 0; bMask < (((int64) (1)) << numSquares); bMask++) {
            int64 occ = initOCCMagicMoves(squares, numSquares, bMask);
            BmagicNOMASK(i, occ) = initBishopMagicsMoves(8 * (i / 8) + (std::abs(i % 8 - 7) % 8), occ);
            //BmagicNOMASK(i, occ) = initBishopMagicsMoves(i, occ);
        }
    }

    for (i = 0; i < 64; i++) {
        int squares[64];
        int numSquares = 0;
        int64 rMask = rookMasks[i];
        while (rMask) {
            int64 bit = rMask & -rMask;
            squares[numSquares++] = bitPos64DB[(bit * 0x07EDD5E59A4E28C2) >> 58];
            rMask ^= bit;
        }
        for (rMask = 0; rMask < (((int64) (1)) << numSquares); rMask++) {
            int64 occ = initOCCMagicMoves(squares, numSquares, rMask);
            //RmagicNOMASK(i, occ) = initRookMagicMoves(8*(i/8) + (std::abs(i%8 - 7) % 8), occ);
            RmagicNOMASK(i, occ) = initRookMagicMoves(i, occ);
        }
    }
}

MagicMoves::MagicMoves() {
    bishopDB[64][1 << 9];
    rookDB[64][1 << 12];
}

#include "Eval.h"

Eval::Eval(Board *board) {
    this->gameBoard = board;
}

// DOES NOT HANDLE CHECK-MATE!!!! search must manually check for mate and set eval = +/- INT_MAX
int Eval::evaluate() {
    const int minorLimit = 2; // endgame if minors <= minor limit
    int blackScore = 0;
    int whiteScore = 0;
    int pieceCounts[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

    // iterate over each square
    // positional evaluation
    for (ESquare sq = A1; sq <= H8; sq++) {
        EPiece piece = this->gameBoard->getPieceAt(sq);
        EColor color = piece > 6 ? BLACK : WHITE;
        switch (piece) {
            case W_PAWN:
                pieceCounts[W_PAWN]++;
                whiteScore += PAWN_WEIGHTS[sq];
                break;
            case B_PAWN:
                pieceCounts[B_PAWN]++;
                blackScore += PAWN_WEIGHTS[VERT_MIRROR_INDEX[sq]];
                break;
            case W_KNIGHT:
                pieceCounts[W_KNIGHT]++;
                whiteScore += KNIGHT_WEIGHTS[sq];
                break;
            case B_KNIGHT:
                pieceCounts[B_KNIGHT]++;
                blackScore += KNIGHT_WEIGHTS[VERT_MIRROR_INDEX[sq]];
                break;
            case W_BISHOP:
                pieceCounts[W_BISHOP]++;
                whiteScore += BISHOP_WEIGHTS[sq];
                break;
            case B_BISHOP:
                pieceCounts[B_BISHOP]++;
                blackScore += BISHOP_WEIGHTS[VERT_MIRROR_INDEX[sq]];
                break;
            case W_ROOK:
                pieceCounts[W_ROOK]++;
                whiteScore += ROOK_WEIGHTS[sq];
                break;
            case B_ROOK:
                pieceCounts[B_ROOK]++;
                blackScore += ROOK_WEIGHTS[VERT_MIRROR_INDEX[sq]];
                break;
            case W_QUEEN:
                pieceCounts[W_QUEEN]++;
                whiteScore += QUEEN_WEIGHTS[sq];
                break;
            case B_QUEEN:
                pieceCounts[B_QUEEN]++;
                blackScore += QUEEN_WEIGHTS[VERT_MIRROR_INDEX[sq]];
                break;
        }
    }

    // piece value evaluation
    whiteScore += pieceCounts[W_PAWN] * PIECE_VALUES[PAWN];
    blackScore += pieceCounts[B_PAWN] * PIECE_VALUES[PAWN];
    whiteScore += pieceCounts[W_KNIGHT] * PIECE_VALUES[KNIGHT];
    blackScore += pieceCounts[B_KNIGHT] * PIECE_VALUES[KNIGHT];
    whiteScore += pieceCounts[W_BISHOP] * PIECE_VALUES[BISHOP];
    blackScore += pieceCounts[B_BISHOP] * PIECE_VALUES[BISHOP];
    whiteScore += pieceCounts[W_ROOK] * PIECE_VALUES[ROOK];
    blackScore += pieceCounts[B_ROOK] * PIECE_VALUES[ROOK];
    whiteScore += pieceCounts[W_QUEEN] * PIECE_VALUES[QUEEN];
    blackScore += pieceCounts[B_QUEEN] * PIECE_VALUES[QUEEN];

    int whiteMinors = pieceCounts[W_ROOK] + pieceCounts[W_BISHOP] + pieceCounts[W_KNIGHT];
    int blackMinors = pieceCounts[B_ROOK] + pieceCounts[B_BISHOP] + pieceCounts[B_KNIGHT];

    bool endgame = (pieceCounts[B_QUEEN] == 0 && pieceCounts[W_QUEEN] == 0)
                   || (whiteMinors <= minorLimit && blackMinors <= minorLimit);

    // TODO: fix this garbage code
    int whiteKing = SHIFTED_SQUARE[get_LSB(this->gameBoard->bb.pcs[W_KING])];
    int blackKing = SHIFTED_SQUARE[get_LSB(this->gameBoard->bb.pcs[B_KING])];

    // decide king values based on game stage
    if(endgame) {
        whiteScore += END_KING_WEIGHTS[whiteKing];
        blackScore += END_KING_WEIGHTS[VERT_MIRROR_INDEX[blackKing]];
    } else {
        whiteScore += MIDDLE_KING_WEIGHTS[whiteKing];
        blackScore += MIDDLE_KING_WEIGHTS[VERT_MIRROR_INDEX[blackKing]];
    }

    return whiteScore - blackScore;
}
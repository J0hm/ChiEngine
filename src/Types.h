#ifndef CHIENGINE_TYPES_H
#define CHIENGINE_TYPES_H

// BitBoard definitions
typedef unsigned long long EBitBoard;
typedef unsigned long long int64;

// Square identifiers
enum ESquare {A1,B1,C1,D1,E1,F1,G1,H1,
    A2,B2,C2,D2,E2,F2,G2,H2,
    A3,B3,C3,D3,E3,F3,G3,H3,
    A4,B4,C4,D4,E4,F4,G4,H4,
    A5,B5,C5,D5,E5,F5,G5,H5,
    A6,B6,C6,D6,E6,F6,G6,H6,
    A7,B7,C7,D7,E7,F7,G7,H7,
    A8,B8,C8,D8,E8,F8,G8,H8,ER};

// ESquare operators
inline ESquare operator++ (ESquare& square) { return (ESquare)(square+1); }
inline ESquare operator++ (ESquare& square, int)
{ ESquare old = square; square = (ESquare) (square + 1); return old; };

// piece identifiers
enum EPiece {EMPTY,W_PAWN,W_KNIGHT,W_BISHOP,W_ROOK,W_QUEEN,W_KING,
    B_PAWN,B_KNIGHT,B_BISHOP,B_ROOK,B_QUEEN,B_KING,INVALID};

// EPiece operators
inline EPiece operator++ (EPiece& piece) { return (EPiece)(piece+1); }
inline EPiece operator++ (EPiece& piece, int)
{ EPiece old = piece; piece = (EPiece) (piece + 1); return old; };

// Opponent colors
enum EColor {WHITE,BLACK,NONE};

#endif //CHIENGINE_TYPES_H

#ifndef CHIENGINE_MOVE_H
#define CHIENGINE_MOVE_H


#include <string>
#include <bitset>
#include <iostream>
#include "Types.h"

class Move {
public:
    const static unsigned int QUIET_FLAG = 0b0000;
    const static unsigned int EP_CAPTURE_FLAG = 0b0101;
    const static unsigned int DOUBLE_PAWN_PUSH_FLAG = 0b0001;
    const static unsigned int CAPTURE_FLAG = 0b0100;
    const static unsigned int PROMOTION_FLAG = 0b1000;
    const static unsigned int KING_SIDE_CASTLING = 0b0010;
    const static unsigned int QUEEN_SIDE_CASTLING = 0b0011;
    const static unsigned int NULL_MOVE = 0;

    // constructors
    inline Move() : bitMove(0), rating(0) {}

    inline Move(int move) : bitMove(move), rating(0) {}

    // getters
    inline ESquare getDest() {
        return (ESquare) (bitMove & 0x3f);
    }

    inline ESquare getOrigin() {
        return (ESquare) ((bitMove >> 6) & 0x3f);
    }

    inline ESquare getFlags() {
        return (ESquare) ((bitMove >> 12) & 0x0f);
    }

    inline PieceType getPieceType() {
        return (PieceType) ((bitMove >> 16) & 0x7);
    }

    inline PieceType getPromotedPieceType() {
        return (PieceType) ((getFlags() & 0b11) + 1);
    }

    inline PieceType getCapturedPieceType() {
        return (PieceType) ((bitMove >> 19) & 0x7);
    }

    inline unsigned int getPreviousCastlingRights() {
        return (bitMove >> 22) & 0xf;
    }

    inline unsigned int getMoveRating() {
        return rating;
    }

    inline unsigned int getMove() {
        return bitMove;
    }

    // setters
    inline void setDestination(ESquare destination) {
        bitMove &= ~0x3f; // clear the first 6 bits
        bitMove |= (destination & 0x3f); // mask on the first 6 bits and OR it with myMoves
    }

    inline void setOrigin(ESquare origin) {
        bitMove &= ~0xfc0;
        bitMove |= ((origin & 0x3f) << 6);
    }

    inline void setFlags(unsigned int flag) {
        bitMove &= ~0xf000;
        bitMove |= ((flag & 0xf) << 12); // Mask on the first 4 bits
    }

    inline void setCapturedPieceType(PieceType type) {
        bitMove &= ~0x380000;
        bitMove |= ((type & 0x7) << 19); // Mask on the first 3 bits
    }

    inline void setPreviousCastlingRights(unsigned int state) // State contains the 4 bits
    {
        bitMove &= ~0x3c00000;
        bitMove |= ((state & 0xf) << 22);
    }

    inline void setMoveRating(unsigned int moveRating) {
        rating = moveRating;
    }

    // predicates
    //isQuiet returns true for quiet AND double pawn push move
    inline bool isQuiet() {
        bool isNotQuiet = getFlags() & 0b1110;
        return !isNotQuiet;
    }

    inline bool isCapture() { return getFlags() & CAPTURE_FLAG; }

    inline bool isEnPassant() { return getFlags() == EP_CAPTURE_FLAG; }

    inline bool isPromotion() { return getFlags() & PROMOTION_FLAG; }

    inline bool isQueenSideCastling() { return getFlags() == QUEEN_SIDE_CASTLING; }

    inline bool isKingSideCastling() { return getFlags() == KING_SIDE_CASTLING; }

    inline bool isCastling() {
        return isKingSideCastling() || isQueenSideCastling();
    }

    inline bool isDoublePawnPush() { return getFlags() == DOUBLE_PAWN_PUSH_FLAG; }

    inline bool isNullMove() { return bitMove == NULL_MOVE; }

    // returns this move in LAN
    std::string toLAN();

    // Equality to check if two moves are identical for killer moves
    inline bool operator==(Move &otherMove) {
        return (getOrigin() == otherMove.getOrigin())
               && (getDest() == otherMove.getDest())
               && (getFlags() == otherMove.getFlags());
    };

    // Defines an order for moves ratings, used to order moves TODO not yet implemented
    inline bool operator<(Move &otherMove) {return getMoveRating() < otherMove.getMoveRating();};
    inline bool operator>(Move &otherMove) {return getMoveRating() > otherMove.getMoveRating();};
    inline bool operator<=(Move &otherMove) {return getMoveRating() <= otherMove.getMoveRating();};
    inline bool operator>=(Move &otherMove) {return getMoveRating() >= otherMove.getMoveRating();};

    // for printing a move for debug
    friend std::ostream& operator<<(std::ostream &os, Move &move) {
        std::bitset<4> flags(move.getFlags());

        unsigned int xOrigin = move.getOrigin() % 8;
        unsigned int yOrigin = move.getOrigin() / 8;

        unsigned int xDestination = move.getDest() % 8;
        unsigned int yDestination = move.getDest() / 8;

        unsigned int moveOrderingScore = move.getMoveRating();

        os << move.toLAN() << " "
             << "Origin: [" << xOrigin << ", " << yOrigin << "] Dest: ["
             << xDestination << ", " << yDestination << "] Flags: " << flags
             << " MO score : " << moveOrderingScore
             << std::endl;

        return os;
    }

private:
    /* 26 bits to represent a move :
     * Castling rights BEFORE move : 4 bits
     * Captured piece              : 3 bits
     * Moved piece type            : 3 bits
     * Flags                       : 4 bits
     * Origin                      : 6 bits
     * Destination                 : 6 bits
     *
     * Castling:
     * Same as FEN, QKqk = 1111, Qk = 1001, etc.
     *
     * Piece types:
	 * 0 Pawn, 1 Knight, 2 Bishop, 3 Rook, 4 Queen, 5 King, 6 no piece type (for null move)
     *
     * Flags: Leftmost bit is promotion bit, the bit after is capture bit.
     * 0    0    0    0	  quiet moves
     * 0    0    0    1	  double pawn push
     * 0    0	 1	  0	  king castle
     * 0	0	 1	  1	  queen castle
     * 0	1	 0	  0	  captures
     * 0	1	 0	  1	  en-passant-capture
     * 1	0	 0	  0	  knight-promotion
     * 1	0	 0	  1	  bishop-promotion
     * 1	0	 1	  0   rook-promotion
     * 1	0	 1	  1	  queen-promotion
     * 1	1	 0	  0	  knight-promo capture
     * 1	1	 0	  1	  bishop-promo capture
     * 1	1	 1	  0	  rook-promo capture
     * 1	1	 1	  1	  queen-promo capture
     */
    unsigned int bitMove;

    // stores the rating for this move
    int rating;
};


#endif //CHIENGINE_MOVE_H

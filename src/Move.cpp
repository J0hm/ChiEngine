#include <array>
#include <sstream>
#include "Move.h"
#include "Algorithms.h"

Move::Move(unsigned int to, unsigned int from, unsigned int movedPiece, unsigned int captured, unsigned int flags,
           unsigned int castlingRights) {
    unsigned int move = 0;

    move |= (to & 0x3F);
    move |= ((from & 0x3F) << 6);
    move |= ((flags & 0xF)<< 12);
    move |= ((movedPiece & 0x7) << 16);
    move |= ((captured & 0x7) << 19);
    move |= ((castlingRights & 0xF) << 22);

    rating = 0;
    bitMove = move;
}

// return this move in long algebraic notation
std::string Move::toLAN() const {
    std::array<std::string, 8> letters = {"a", "b", "c", "d", "e", "f", "g", "h"};

    unsigned int xOrigin = getOrigin() % 8;
    unsigned int yOrigin = (getOrigin() / 8) + 1;

    unsigned int xDestination = getDest() % 8;
    unsigned int yDestination = (getDest() / 8) + 1;

    std::string promotionLetter;
    if (isPromotion()) {
        unsigned int promotedType = getFlags() - Move::PROMOTION_FLAG + 1;

        if (isCapture()) {
            promotedType -= Move::CAPTURE_FLAG;
        }

        if (promotedType == PieceType::KNIGHT) {
            promotionLetter = "n";
        } else if (promotedType == PieceType::BISHOP) {
            promotionLetter = "b";
        } else if (promotedType == PieceType::ROOK) {
            promotionLetter = "r";
        } else if (promotedType == PieceType::QUEEN) {
            promotionLetter = "q";
        }
    }

    std::stringstream ss;
    ss << letters[xOrigin] << yOrigin << letters[xDestination] << yDestination << promotionLetter;

    return ss.str();
}


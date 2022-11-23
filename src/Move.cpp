#include <array>
#include <sstream>
#include "Move.h"
#include "Algorithms.h"

// return this move in long algebraic notation
std::string Move::toLAN() {
    std::array<std::string, 8> letters = {"a", "b", "c", "d", "e", "f", "g", "h"};

    unsigned int xOrigin = getOrigin() % 8;
    unsigned int yOrigin = (getOrigin() / 8) + 1;

    unsigned int xDestination = getDest() % 8;
    unsigned int yDestination = (getDest() / 8) + 1;

    std::string promotionLetter = "";
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

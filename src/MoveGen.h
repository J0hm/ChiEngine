#ifndef CHIENGINE_MOVEGEN_H
#define CHIENGINE_MOVEGEN_H

// pre-initialize attacks for knights
// magic bitboards for bishop/rook, NEED: int64 mask, int64 magic number for each square for rook/bishop
// probably want to add popLSB/getLSB, also might want to move the others from board.h to types.h
// TODO: knight attack table, king attack table, bishop/rook occupancy masks, magics
// want: isLegal(Move), MoveGen initialized with a pointer to the board
// get attacks for each piece
// enum for EVASIONS, LEGAL, PSEUDO_LEGAL?
// efficient checking for checks, check if a move puts the king in check
class MoveGen {

};


#endif //CHIENGINE_MOVEGEN_H

#ifndef CHIENGINE_TTABLE_H
#define CHIENGINE_TTABLE_H

#include "Types.h"
#include "Move.h"
#include <optional>


/* Indexed by zobrist hash % hashSize (use bitshift bc powers of 2)
 * Want to store: full hash (for validation), depth, eval, best move, flag (exact, beta, alpha)
 */

enum HashType {HASH_EXACT, HASH_BETA, HASH_ALPHA, HASH_NONE};

const unsigned int size = 24;

struct Transposition {
    bool hasEntry{}; // used to check if there is actually an entry at this position
    int64 hash{};
    HashType hashType{};
    unsigned int depth{};
    int eval{};
    Move bestMove{};

};

class TTable {
public:
    explicit TTable();

    void reset();

    bool hasKey(int64 key);                         // does this TTable contain a value at the given key?
    Transposition getEntry(int64 key);              // gets the transposition for the given key
    void setTTEntry(int64 hash, HashType type, unsigned int depth, int eval, Move bestMove);    // sets the value at the given key to t

private:
    Transposition table[1<<size];
    int64 keyMask = (1<<size)-1;

    int64 getInternalKey(int64 key) const;
};


#endif //CHIENGINE_TTABLE_H

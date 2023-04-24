#ifndef CHIENGINE_TTABLE_H
#define CHIENGINE_TTABLE_H

#include "Types.h"
#include "Move.h"


/* Indexed by zobrist hash % hashSize (use bitshift bc powers of 2)
 * Want to store: full hash (for validation), depth, eval, best move, flag (exact, beta, alpha)
 */

enum HashType {HASH_EXACT, HASH_BETA, HASH_ALPHA};

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
    explicit TTable(unsigned int size);

    bool hasKey(int64 key);                       // does this TTable contain a value at the given key?
    Transposition getEntry(int64 key);            // gets the transposition for the given key
    void setEntry(int64 key, Transposition t);    // sets the value at the given key to t

private:
    Transposition *table;
    int64 keyMask;

    int64 getInternalKey(int64 key) const;
};


#endif //CHIENGINE_TTABLE_H

#include "TTable.h"

TTable::TTable() = default;

bool TTable::hasKey(int64 key) {
    return getEntry(key).hasEntry;
}

Transposition TTable::getEntry(int64 key) {
    return table[getInternalKey(key)];
}

void TTable::setTTEntry(int64 hash, HashType type, unsigned int depth, int eval, Move bestMove) {
    table[getInternalKey(hash)] = {true, hash, type, depth, eval, bestMove};
}

int64 TTable::getInternalKey(int64 key) const {
    key &= keyMask;
    return key;
}

void TTable::reset() {
//    std::cout << "reset transposition table\n";
    for(Transposition t : table) {
        t.hasEntry = false;
    }
}

#include "TTable.h"

TTable::TTable(unsigned int size) : table(new Transposition[2^size]) {
    keyMask = (1<<size)-1;
}

bool TTable::hasKey(int64 key) {
    return getEntry(key).hasEntry;
}

Transposition TTable::getEntry(int64 key) {
    return table[getInternalKey(key)];
}

void TTable::setEntry(int64 key, Transposition t) {
    table[getInternalKey(key)] = t;
}

int64 TTable::getInternalKey(int64 key) const {
    return key & keyMask;
};


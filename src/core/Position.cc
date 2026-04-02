#include "core/Position.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Position& pos) {
    os << "(" << pos.row << ", " << pos.col << ")";
    return os;
}

Position Position::operator/(int scalar){
    return {row / scalar, col / scalar};
}

bool Position::operator==(const Position& other) const{
    return row == other.row && col == other.col;
}

size_t Hasher::operator() (const Position& p) const{
    size_t hash = p.row ^ (p.col << 1);
    return hash;
}

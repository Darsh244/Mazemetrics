#include "../include/Position.h"
#include <iostream>
#include <ostream>

std::ostream& operator<<(std::ostream& os, const Position& pos) {
    os << "(" << pos.row << ", " << pos.col << ")";
    return os;
}

Position Position::operator/(int scalar){
    return {row / scalar, col / scalar};
}
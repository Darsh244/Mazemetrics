#pragma once
#include <ostream>

struct Position {
    int row;
    int col;

    Position operator/(int scalar);
    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};

#pragma once
#include <ostream>

struct Position {
    int row;
    int col;

    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};

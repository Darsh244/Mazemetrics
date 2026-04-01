#pragma once
#include <ostream>

struct Position {
    int row;
    int col;

    bool operator==(const Position& other) const;
    Position operator/(int scalar);
    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};

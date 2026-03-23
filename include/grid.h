#include "block.h"

class Grid {
    int rows;
    int columns;
    std::vector<Block> blocks;
    public:
        Grid(int rows, int columns) : rows(rows), columns(columns) {}
        void fill(const sf::Vector2u windowSize);
        void draw(sf::RenderWindow& win);
};
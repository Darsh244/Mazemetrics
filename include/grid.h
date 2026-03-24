#include "block.h"

class Grid {
    int rows;
    int columns;
    std::vector<std::vector<Block>> blocks;
    sf::VertexArray blocksArray;
    public:
        Grid(int rows, int columns) : rows(rows), columns(columns) {}
        void fill(const sf::Vector2u windowSize);
        void draw(sf::RenderWindow& win);
        void generateMaze();
};
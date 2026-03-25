#include "block.h"


namespace COLOR {
    const sf::Color RED(255, 0, 0);
    const sf::Color GREEN(0, 255, 0);
    const sf::Color LBLUE(173, 216, 230);
    const sf::Color GREY(128, 128, 128);
    const sf::Color BLACK(0, 0, 0);
    const sf::Color YELLOW(255, 255, 0);
    const sf::Color WHITE(255, 255, 255);

};


class Grid {
    int rows;
    int columns;
    std::vector<std::vector<Block>> blocks;
    sf::VertexArray vertices;
    public:
        Grid(int r, int c);
        sf::Vertex* getBlockVertices(int r, int c);
        void setBlockPosition(int r, int c, float blockSize);
        void setBlockColor(int r, int c, const Type type);
        void fill(const sf::Vector2u windowSize);
        void draw(sf::RenderWindow& win);
        void generateMaze();
};
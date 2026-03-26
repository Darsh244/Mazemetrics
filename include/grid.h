#include "block.h"
#include <random>
#include <vector>

namespace COLOR {
    const sf::Color RED(255, 0, 0);
    const sf::Color GREEN(0, 255, 0);
    const sf::Color LBLUE(173, 216, 230);
    const sf::Color LGREY(245, 245, 245);
    const sf::Color BLACK(0, 0, 0);
    const sf::Color YELLOW(255, 255, 0);
    const sf::Color WHITE(255, 255, 255);

};


class Grid {
    int rows;
    int columns;
    sf::VertexArray vertices;
    std::vector<std::vector<Block>> blocks;
    public:
        Grid(int r, int c);
        void fill(const sf::Vector2u windowSize);
        void draw(sf::RenderWindow& win);
        void generateMaze();
        bool generationDone() {return mazeGenerated;}
    
    private:
        struct Cell {
            int row;
            int col;
        };
        struct Wall {
            Cell Cell1;
            Cell Cell2;
        };

        std::mt19937 generator;
        bool mazeGenerated;

        Cell getRandomCell();
        sf::Vertex* getBlockVertices(Cell cell);
        Block& getBlock(Cell cell);
        const Type getCellType(Cell cell);
        Cell getUnvisited(Wall& wall);
        std::pair<Wall, int> getRandomWallDetails(std::vector<Wall>& wallList);

        void addWalls(Cell cell,  std::vector<Wall>& wallList);
        void popWall(int index, std::vector<Wall>& wallList);

        void setCellType(Cell cell, const Type type);
        void setBlockPosition(Cell cell, float blockSize);
        void setBlockColor(Cell cell, const Type type);

        bool outOfBounds(Cell cell);
        bool onlyOneVisited(Wall& wall);

};
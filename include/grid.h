#pragma once
#include "Block.h"
#include <random>
#include <vector>

struct Position;
enum class Type : int;

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
        void reset(const sf::Vector2u windowSize);
        int getRows() const {return rows;}
        int getColumns() const {return columns;}
    
    private:  
        void setBlockPosition(Position pos, float blockSize);
        void setBlockColor(Position pos, const Type type);

        Block& getBlockAtPos(Position pos);
        sf::Vertex* getVerticesOfBlockAtPos(Position blockPos);


        friend class MazeGenerator;

};
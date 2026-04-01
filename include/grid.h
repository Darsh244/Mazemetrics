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
    const sf::Color GOLD (255, 215, 0);
    const sf::Color WHITE(255, 255, 255);

};


class Grid {
    int rows;
    int columns;
    float blockSize;
    sf::VertexArray vertices;
    std::vector<std::vector<Block>> blocks;
    public:
        Grid(int r, int c);
        void fill(const sf::Vector2u windowSize);
        void draw(sf::RenderWindow& win);
        void reset(const sf::Vector2u windowSize);
        int getRows() const {return rows;}
        int getColumns() const {return columns;}
        float getBlockSize() const {return blockSize;}
    
    private:
      
        void setBlockPosition(Position pos);
        void setBlockColor(Position pos, const Type type);
        void setBlockType(Position blockPos, const Type type);

        Block& getBlockAtPos(Position pos);
        sf::Vertex* getBlockVertices(Position blockPos);
        Block& getBlock(Position blockPos);
        Type getBlockType(Position blockPos);

        bool outOfBounds(Position blockPos);


        friend class MazeGenerator;
        friend class PathFinder;

};
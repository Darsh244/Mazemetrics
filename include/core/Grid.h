#pragma once
#include "Block.h"
#include <random>
#include <vector>

struct Position;
enum class Type : int;
class Grid {
    int rows;
    int columns;
    float blockSize;
    sf::VertexArray vertices;
    std::vector<std::vector<Block>> blocks;
    public:
        Grid(sf::Vector2u grid_size);
        void fill(const sf::Vector2u windowSize);
        void reset(const sf::Vector2u windowSize);

        int getRows() const {return rows;}
        int getColumns() const {return columns;}
        float getBlockSize() const {return blockSize;}
        sf::VertexArray& getVertexArray() {return vertices;}
    
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
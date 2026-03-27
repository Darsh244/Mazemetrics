#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>


class Grid;
class Block;
struct Position;
enum class Type : int;

class MazeGenerator{
    protected: 
        Grid& grid;
        std::mt19937 generator;
        bool mazeGenerated;

        bool outOfBounds(Position blockPos);

        sf::Vertex* getBlockVertices(Position blockPos);
        Block& getBlock(Position blockPos);
        Type getBlockType(Position blockPos);

        void setBlockType(Position blockPos, const Type type);

        void setBlockPosition(Position blockPos, float blockSize);
        void setBlockColor(Position blockPos, const Type type);

        int getGridRows() const;
        int getGridColumns() const;

    public:
        MazeGenerator(Grid& g, unsigned int seed = std::random_device{}());
        virtual void  generateMaze() = 0;
        bool generationDone() {return mazeGenerated;}
        virtual ~MazeGenerator() {}

};

#pragma once
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

        int getRows() const;
        int getColumns() const;
        void setBlockType(Position blockPos, const Type type);
        
        Type getBlockType(Position blockPos);

        bool outOfBounds(Position blockPos);

    public:
        MazeGenerator(Grid& g, unsigned int seed = std::random_device{}());
        virtual void  generateMaze() = 0;
        virtual void generateMazeStep(int batchSize = 1) {}
        bool generationDone() {return mazeGenerated;}
        virtual ~MazeGenerator() {}

};

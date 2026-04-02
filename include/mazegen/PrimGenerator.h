#pragma once
#include "../core/Position.h"
#include "MazeGenerator.h"

class PrimGenerator : public MazeGenerator {
    struct Wall {
        Position PosBlock1;
        Position PosBlock2;
    };
    std::vector<Wall> wallList;

    public :
        PrimGenerator(Grid& g, unsigned int seed = std::random_device{}());
        void generateMaze() override;
        void generateMazeStep(int batchSize = 1) override;
    
    private:
        Position activeBlock;
        bool hasActive;

        Position getRandomPosition();
        Position getUnvisited(Wall& wall);
        std::pair<Wall, int> getRandomWallDetails(std::vector<Wall>& wallList, bool bias);

        void addWalls(Position pos,  std::vector<Wall>& wallList);
        void popWall(int index, std::vector<Wall>& wallList);
        void setActiveBlock(Position blockPos);

        bool onlyOneVisited(Wall& wall);
};
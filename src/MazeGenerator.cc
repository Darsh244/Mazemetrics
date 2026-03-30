#include "../include/MazeGenerator.h"
#include "../include/Position.h"
#include "../include/Grid.h"


int MazeGenerator::getRows() const {
        return grid.getRows();
}

int MazeGenerator::getColumns() const {
        return grid.getColumns();
}

void MazeGenerator::setBlockType(Position blockPos, const Type type) {
        grid.setBlockType(blockPos, type);
}

Type MazeGenerator::getBlockType(Position blockPos){
        return grid.getBlockType(blockPos);
}

bool MazeGenerator::outOfBounds(Position blockPos){
        return grid.outOfBounds(blockPos);
}

MazeGenerator::MazeGenerator(Grid& grid, unsigned int seed) : 
        grid(grid), mazeGenerated(false), generator(seed) {}
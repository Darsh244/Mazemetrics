#include "../include/MazeGenerator.h"
#include "../include/Position.h"
#include "../include/Grid.h"
#include "Block.h"

bool MazeGenerator::outOfBounds(Position blockPos){
    int rows = getGridRows();
    int columns = getGridColumns();
    return blockPos.row < 0 || blockPos.row >= rows || blockPos.col < 0 || blockPos.col >= columns;
}

sf::Vertex* MazeGenerator::getBlockVertices(Position blockPos){
    return grid.getVerticesOfBlockAtPos(blockPos);   
}

Block& MazeGenerator::getBlock(Position blockPos){
    return grid.getBlockAtPos(blockPos);
}

Type MazeGenerator::getBlockType(Position blockPos){
    return getBlock(blockPos).getType();
}

void MazeGenerator::setBlockType(Position blockPos, const Type type){
    getBlock(blockPos).setType(type);
    setBlockColor(blockPos, type);
}

void MazeGenerator::setBlockPosition(Position blockPos, float blockSize){
    grid.setBlockPosition(blockPos, blockSize);
}

void MazeGenerator::setBlockColor(Position blockPos, const Type type){
    grid.setBlockColor(blockPos, type);
}

int MazeGenerator::getGridRows() const {
    return grid.getRows();
}

int MazeGenerator::getGridColumns() const { 
    return grid.getColumns();
}

MazeGenerator::MazeGenerator(Grid& grid, unsigned int seed) : 
        grid(grid), mazeGenerated(false), generator(seed) {}
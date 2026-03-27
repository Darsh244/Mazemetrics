#include "../include/PrimGenerator.h"
#include  "../include/Block.h"


PrimGenerator::PrimGenerator(Grid& g, unsigned int seed) : MazeGenerator(g, seed) {
    int rows = getGridRows();
    int columns = getGridColumns();
    wallList.reserve(rows * columns / 2);
}


void PrimGenerator::generateMaze(){
    Position starting_position = getRandomPosition();
    setBlockType(starting_position, Type::VISITED); 
    addWalls(starting_position, wallList);
    while(!wallList.empty()){
        std::pair<Wall, int> randomWallDetails = getRandomWallDetails(wallList);
        Wall randomWall = randomWallDetails.first;
        popWall(randomWallDetails.second, wallList);
        if (onlyOneVisited(randomWall)){
            Position unvisited = getUnvisited(randomWall);
            Position between = { // since every pair of blocks have 2 units gap
                (randomWall.PosBlock1.row + randomWall.PosBlock2.row) / 2,
                (randomWall.PosBlock1.col + randomWall.PosBlock2.col) / 2,
            };
            setBlockType(unvisited, Type::VISITED);
            setBlockType(between, Type::PASSAGE);
            addWalls(unvisited, wallList);
        }
    }

    mazeGenerated = true;
    
}


Position PrimGenerator::getRandomPosition(){
    int rows = getGridRows();
    int columns = getGridColumns();
    std::uniform_int_distribution<int> rowDist(0, ((rows + 1) / 2) - 1); // rows = 2 * r - 1 
    std::uniform_int_distribution<int> colDist(0, ((columns + 1) / 2) - 1);
    return {rowDist(generator) * 2 + 1, colDist(generator) * 2 + 1}; // unvisited blocks are on odd positions
}

Position PrimGenerator::getUnvisited(Wall& wall){
    if (getBlockType(wall.PosBlock1) == Type::UNVISITED) return wall.PosBlock1;
    else return wall.PosBlock2;
}

std::pair<PrimGenerator::Wall, int> PrimGenerator::getRandomWallDetails(std::vector<Wall>& wallList){
    std::uniform_int_distribution<int> dist(0, wallList.size() - 1);
    int index = dist(generator);
    return {wallList[index], index};
}

void PrimGenerator::addWalls(Position blockPos, std::vector<Wall>& wallList){
    int dr[] = {-2, 0, 2, 0}; // row offsets
    int dc[] = {0, 2, 0, -2}; // col offsets
    std::vector<int> indices = {0, 1, 2, 3};
    std::shuffle(indices.begin(), indices.end(), generator);
    for (int i : indices){
        Position neighbour = {blockPos.row + dr[i], blockPos.col + dc[i]};
        if (!outOfBounds(neighbour) && getBlockType(neighbour) == Type::UNVISITED){
            wallList.push_back({blockPos, neighbour});
        }
    }
}

void PrimGenerator::popWall(int index, std::vector<Wall>& wallList){
    std::swap(wallList[index], wallList.back());
    wallList.pop_back();
}

bool PrimGenerator::onlyOneVisited(Wall& wall){
    Type type1 = getBlockType(wall.PosBlock1);
    Type type2 = getBlockType(wall.PosBlock2);
    return ((type1 == Type::VISITED && type2 == Type::UNVISITED) ||
            (type1 == Type::UNVISITED && type2 == Type::VISITED));
}


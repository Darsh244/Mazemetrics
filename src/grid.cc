#include "../include/grid.h"
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>

Grid::Grid(int r, int c){
    rows = 2 * r + 1;
    columns = 2 * c + 1;
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(rows * columns * 6);

    std::random_device rd; // random seed
    generator.seed(rd());
    mazeGenerated = false;
}



void Grid::draw(sf::RenderWindow &win){
    win.draw(vertices);
}

void Grid::fill(const sf::Vector2u windowSize){
    blocks.reserve(rows * columns);

    float blockSize = std::min(
        float(windowSize.x) / columns,
        float(windowSize.y) / rows
    ); // each block should be a square
  
    for (int row = 0; row < rows; ++ row){
        std::vector<Block> currentRow;
        for (int col = 0; col < columns; ++ col){

            Block block(Type::WALL); // even indices are walls
            if (row % 2 == 1 && col % 2 == 1){ // odd indices are paths
                block.setType(Type::UNVISITED);
            }
            currentRow.push_back(block);

            setBlockPosition({row, col}, blockSize);
            setBlockColor({row, col}, block.getType());
        }
        blocks.push_back(currentRow);
    }
}



sf::Vertex* Grid::getBlockVertices(Cell cell){
    int r = cell.row;
    int c = cell.col;
    return &vertices[(r * columns + c) * 6];
}

void Grid::setBlockPosition(Cell cell, float blockSize){
    int r = cell.row;
    int c = cell.col;
    sf::Vertex* blockVertices = getBlockVertices(cell);
    blockVertices[0].position = sf::Vector2f(c * blockSize, r * blockSize);
    blockVertices[1].position = sf::Vector2f(c * blockSize + blockSize, r * blockSize);
    blockVertices[2].position = sf::Vector2f(c* blockSize + blockSize, r * blockSize + blockSize);
    blockVertices[3].position = sf::Vector2f(c* blockSize + blockSize, r * blockSize + blockSize);
    blockVertices[4].position = sf::Vector2f(c* blockSize, r * blockSize + blockSize);
    blockVertices[5].position = sf::Vector2f(c * blockSize, r * blockSize);
}


void Grid::setBlockColor(Cell cell, const Type type){
    sf::Color color;
    switch (type) {
        case VISITED:
            color = COLOR::LGREY;
            break;
        case UNVISITED:
            color = COLOR::BLACK;
            break;  
        case WALL:
            color = COLOR::BLACK;
            break;   
    }

    sf::Vertex* block = getBlockVertices(cell);
    for (int i = 0; i < 6; ++i){
        block[i].color = color;
    }
}


bool Grid::outOfBounds(Cell cell){
    return cell.row < 0 || cell.row >= rows || cell.col < 0 || cell.col >= columns;
}


Block& Grid::getBlock(Cell cell){
    return blocks[cell.row][cell.col];
}

const Type Grid::getCellType(Cell cell){
    return getBlock(cell).getType();
}


void Grid::generateMaze(){
    std::vector<Wall> wallList;
    wallList.reserve(rows * columns / 2);

    Cell starting_cell = getRandomCell();
    setCellType(starting_cell, Type::VISITED); 
    addWalls(starting_cell, wallList);
    while(!wallList.empty()){
        std::pair<Wall, int> randomWallDetails = getRandomWallDetails(wallList);
        Wall randomWall = randomWallDetails.first;
        popWall(randomWallDetails.second, wallList);
        if (onlyOneVisited(randomWall)){
            Cell unvisited = getUnvisited(randomWall);
            Cell between = {
                (randomWall.Cell1.row + randomWall.Cell2.row) / 2,
                (randomWall.Cell1.col + randomWall.Cell2.col) / 2,
            };
            setCellType(unvisited, Type::VISITED);
            setCellType(between, Type::VISITED);
            addWalls(unvisited, wallList);
        }
    }

    mazeGenerated = true;
    
}


Grid::Cell Grid::getUnvisited(Wall& wall){
    if (getCellType(wall.Cell1) == Type::UNVISITED) return wall.Cell1;
    else return wall.Cell2;
}

bool Grid::onlyOneVisited(Wall& wall){
    Type type1 = getCellType(wall.Cell1);
    Type type2 = getCellType(wall.Cell2);
    return ((type1 == Type::VISITED && type2 == Type::UNVISITED) ||
            (type1 == Type::UNVISITED && type2 == Type::VISITED)); 
}


void Grid::popWall(int index, std::vector<Wall>& wallList){
    std::swap(wallList[index], wallList.back());
    wallList.pop_back();
}



std::pair<Grid::Wall, int> Grid::getRandomWallDetails(std::vector<Wall>& wallList){
    std::uniform_int_distribution<int> dist(0, wallList.size() - 1);
    int index = dist(generator);
    return {wallList[index], index};
}

void Grid::addWalls(Cell cell, std::vector<Wall>& wallList){
    int dr[] = {-2, 0, 2, 0}; // row offsets
    int dc[] = {0, 2, 0, -2}; // col offsets
    std::vector<int> indices = {0, 1, 2, 3};
    std::shuffle(indices.begin(), indices.end(), generator);
    for (int i : indices){
        Cell neighbour = {cell.row + dr[i], cell.col + dc[i]};
        if (!outOfBounds(neighbour) && getCellType(neighbour) == Type::UNVISITED){
            wallList.push_back({cell, neighbour});
        }
    }
}


void Grid::setCellType(Cell cell, const Type type){
    getBlock(cell).setType(type);
    setBlockColor(cell, type);
}

Grid::Cell Grid::getRandomCell(){
    std::uniform_int_distribution<int> rowDist(0, (rows - 2) / 2);
    std::uniform_int_distribution<int> colDist(0, (columns - 2) / 2);
    return {rowDist(generator) * 2 + 1, colDist(generator) * 2 + 1};
}



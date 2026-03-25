#include "../include/grid.h"
#include <random>
#include <vector>
#include <iostream>

Grid::Grid(int r, int c){
    rows = r;
    columns = c;
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
            Block block(Type::OBSTACLE);
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
        case OBSTACLE:
            color = COLOR::BLACK;
            break;
        case PATH:
            color = COLOR::YELLOW;
            break;
        case START:
            color = COLOR::GREEN;
            break;
        case END:
            color = COLOR::RED;  
            break;      
        case VISITED:
            color = COLOR::LBLUE;
            break;
        case UNVISITED:
            color = COLOR::LGREY;
            break;     
    }

    sf::Vertex* block = getBlockVertices(cell);
    for (int i = 0; i < 6; ++i){
        block[i].color = color;
    }
}


void Grid::generateMaze(){
    Cell starting_cell = getRandomCell();
    setCellType(starting_cell, Type::UNVISITED); // UNVISITED are Passages

    std::vector<Cell> frontierList;
    std::vector<Cell> neighbourPassages;
    frontierList.reserve(rows * columns);
    neighbourPassages.reserve(4);
    processNeighbours(starting_cell, frontierList, neighbourPassages);

    while(!frontierList.empty()){
        std::pair<Grid::Cell, int> randomCellDetails = getRandomCellDetails(frontierList);
        processNeighbours(randomCellDetails.first, frontierList, neighbourPassages);
        Cell randomPassage = getRandomCellDetails(neighbourPassages).first;
        carve(randomCellDetails.first, randomPassage); // marking the wall between frontier and neighbour as Passage
        setCellType(randomCellDetails.first, Type::UNVISITED); // marking current frontier as Passage
        popFrontierCell(randomCellDetails.second, frontierList);     
    }

    mazeGenerated = true;
    
}

void Grid::popFrontierCell(int index, std::vector<Cell>& frontierList){
    std::swap(frontierList[index], frontierList.back());
    frontierList.pop_back();
}


void Grid::carve(Cell& frontierCell, Cell& passageCell){
    // calculating direction of wall in between passageCell and frontierCell
    int direction[] = {(passageCell.row - frontierCell.row) / 2, (passageCell.col - frontierCell.col) / 2};
    setCellType(
        {frontierCell.row + direction[0], frontierCell.col + direction[1]},
        Type::UNVISITED
    );
}


void Grid::processNeighbours(Cell cell, std::vector<Cell>& frontierList, std::vector<Cell>& passages){
    int dr[] = {-2, 0, 2, 0}; // row offsets
    int dc[] = {0, 2, 0, -2}; // col offsets
    passages.clear();

    for (int i = 0; i < 4; ++i){
        Cell neighbour = {cell.row + dr[i], cell.col + dc[i]};
        if (!outOfBounds(neighbour)){
            if (getCellType(neighbour) == Type::OBSTACLE){
                frontierList.push_back(neighbour);
            }
            else if (getCellType(neighbour) == Type::UNVISITED){
                passages.push_back(neighbour);
            }
        }
    }
}


bool Grid::outOfBounds(Cell cell){
    return cell.row < 0 || cell.row >= rows || cell.col < 0 || cell.col >= columns;
}


void Grid::setCellType(Cell cell, const Type type){
    getBlock(cell).setType(type);
    setBlockColor(cell, type);
}

Block& Grid::getBlock(Cell cell){
    return blocks[cell.row][cell.col];
}

const Type Grid::getCellType(Cell cell){
    return getBlock(cell).getType();
}

Grid::Cell Grid::getRandomCell(){
    std::uniform_int_distribution<int> rowDist(0, rows - 1); // maps input to random number in range (inclusive)
    std::uniform_int_distribution<int> colDist(0, columns - 1);
    return {rowDist(generator), colDist(generator)};
}

std::pair<Grid::Cell, int> Grid::getRandomCellDetails(std::vector<Cell>& cells){
    std::uniform_int_distribution<int> dist(0, cells.size() - 1);
    int index = dist(generator);
    return {cells[index], index};
}


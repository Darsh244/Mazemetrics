#include "core/Grid.h"
#include "core/Position.h"
#include "renderer/Renderer.h"

Grid::Grid(sf::Vector2u grid_size){
    rows = 2 * grid_size.x + 1; // Block Block -> Wall Block Wall Block Wall
    columns = 2 * grid_size.y + 1;
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(rows * columns * 6);
}


void Grid::fill(const sf::Vector2u windowSize){
    blocks.reserve(rows);

    blockSize = floor(std::min(
        float(windowSize.x) / columns,
        float(windowSize.y) / rows
    )); // each block should be a square
    
    for (int row = 0; row < rows; ++ row){
        std::vector<Block> currentRow;
        for (int col = 0; col < columns; ++ col){

            Block block(Type::WALL); // want border to be WALL so any even coord = Wall
            if (row % 2 == 1 && col % 2 == 1){
                block.setType(Type::UNVISITED);
            }
            currentRow.push_back(block);

            setBlockPosition({row, col});
            setBlockColor({row, col}, block.getType());
        }
        blocks.push_back(currentRow);
    }
}

void Grid::reset(const sf::Vector2u windowSize){
    blocks.clear();
    fill(windowSize);
}



void Grid::setBlockPosition(Position blockPos){
    int r = blockPos.row;
    int c = blockPos.col;
    sf::Vertex* blockVertices = getBlockVertices(blockPos);
    blockVertices[0].position = sf::Vector2f(c * blockSize, r * blockSize);
    blockVertices[1].position = sf::Vector2f(c * blockSize + blockSize, r * blockSize);
    blockVertices[2].position = sf::Vector2f(c* blockSize + blockSize, r * blockSize + blockSize);
    blockVertices[3].position = sf::Vector2f(c* blockSize + blockSize, r * blockSize + blockSize);
    blockVertices[4].position = sf::Vector2f(c* blockSize, r * blockSize + blockSize);
    blockVertices[5].position = sf::Vector2f(c * blockSize, r * blockSize);
}


void Grid::setBlockColor(Position blockPos, const Type type){
    sf::Color color;
    switch (type) {
        case Type::VISITED:
            color = COLOR::LGREY;
            break;
        case Type::UNVISITED:
            color = COLOR::BLACK;
            break;  
        case Type::WALL:
            color = COLOR::BLACK;
            break;
        case Type::PASSAGE:
            color = COLOR::LGREY;
            break;
        case Type::ACTIVE:
            color = COLOR::RED;
            break;
        case Type::START:
            color = COLOR::GREEN;
            break;
        case Type::END:
            color = COLOR::RED;
            break;
        case Type::EXPLORED:
            color = COLOR::LBLUE;
            break;
        case Type::PATH:
            color = COLOR::GOLD;
            break;
    }

    sf::Vertex* block = getBlockVertices(blockPos);
    for (int i = 0; i < 6; ++i){
        block[i].color = color;
    }
}

void Grid::setBlockType(Position blockPos, const Type type){
    getBlock(blockPos).setType(type);
    setBlockColor(blockPos, type);
}


Block& Grid::getBlockAtPos(Position blockPos){
    return blocks[blockPos.row][blockPos.col];
}

sf::Vertex* Grid::getBlockVertices(Position blockPos){
    int r = blockPos.row;
    int c = blockPos.col;
    return &vertices[(r * columns + c) * 6];
}

Block& Grid::getBlock(Position blockPos){
    return blocks[blockPos.row][blockPos.col];
}

Type Grid::getBlockType(Position blockPos){
    return getBlock(blockPos).getType();
}

bool Grid::outOfBounds(Position blockPos){
    return blockPos.row < 0 || blockPos.row >= rows || blockPos.col < 0 || blockPos.col >= columns;
}



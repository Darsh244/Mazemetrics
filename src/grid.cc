#include "../include/Grid.h"
#include "../include/Block.h"
#include "../include/Position.h"

Grid::Grid(int r, int c){
    rows = 2 * r + 1; // Block Block -> Wall Block Wall Block Wall
    columns = 2 * c + 1;
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(rows * columns * 6);
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

            Block block(Type::WALL); // taking positions with any even entry as WALL because we want border to be WALLS
            if (row % 2 == 1 && col % 2 == 1){ 
                block.setType(Type::UNVISITED);
            }
            currentRow.push_back(block);

            setBlockPosition({row, col}, blockSize);
            setBlockColor({row, col}, block.getType());
        }
        blocks.push_back(currentRow);
    }
}


sf::Vertex* Grid::getVerticesOfBlockAtPos(Position blockPos){
    int r = blockPos.row;
    int c = blockPos.col;
    return &vertices[(r * columns + c) * 6];
}

void Grid::setBlockPosition(Position blockPos, float blockSize){
    int r = blockPos.row;
    int c = blockPos.col;
    sf::Vertex* blockVertices = getVerticesOfBlockAtPos(blockPos);
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
    }

    sf::Vertex* block = getVerticesOfBlockAtPos(blockPos);
    for (int i = 0; i < 6; ++i){
        block[i].color = color;
    }
}


Block& Grid::getBlockAtPos(Position blockPos){
    return blocks[blockPos.row][blockPos.col];
}



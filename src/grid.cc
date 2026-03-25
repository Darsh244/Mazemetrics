#include "../include/grid.h"

Grid::Grid(int r, int c){
    rows = r;
    columns = c;
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(rows * columns * 6);
}


sf::Vertex* Grid::getBlockVertices(int r, int c){
    return &vertices[(r * columns + c) * 6];
}

void Grid::setBlockPosition(int r, int c, float blockSize){
    sf::Vertex* blockVertices = getBlockVertices(r, c);
    blockVertices[0].position = sf::Vector2f(c * blockSize, r * blockSize);
    blockVertices[1].position = sf::Vector2f(c * blockSize + blockSize, r * blockSize);
    blockVertices[2].position = sf::Vector2f(c* blockSize + blockSize, r * blockSize + blockSize);
    blockVertices[3].position = sf::Vector2f(c* blockSize + blockSize, r * blockSize + blockSize);
    blockVertices[4].position = sf::Vector2f(c* blockSize, r * blockSize + blockSize);
    blockVertices[5].position = sf::Vector2f(c * blockSize, r * blockSize);
}


void Grid::setBlockColor(int r, int c, const Type type){
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
            color = COLOR::GREY;
            break;     
    }

    sf::Vertex* block = getBlockVertices(r, c);
    for (int i = 0; i < 6; ++i){
        block[i].color = color;
    }
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

            setBlockPosition(row, col, blockSize);
            setBlockColor(row, col, block.getType());
        }
        blocks.push_back(currentRow);
    }
}


void Grid::draw(sf::RenderWindow &win){
    win.draw(vertices);
}
#include "../include/grid.h"

void Grid::fill(const sf::Vector2u windowSize){
    blocks.reserve(rows * columns);

    float blockSize = std::min(
        float(windowSize.x) / columns,
        float(windowSize.y) / rows
    ); // each block should be a square
  
    for (int row = 0; row < rows; ++ row){
        std::vector<Block> rowBlocks;
        for (int col = 0; col < columns; ++ col){
            Block block({blockSize, blockSize}, Type::OBSTACLE);
            block.setPos({col * blockSize, row * blockSize});
            rowBlocks.push_back(block);
        }
        blocks.push_back(rowBlocks);
    }
}


void Grid::draw(sf::RenderWindow &win){
    for (int row = 0; row < rows; ++ row){
        for (int col = 0; col < columns; ++col){
            blocks[row][col].draw(win);
        }
    }
}
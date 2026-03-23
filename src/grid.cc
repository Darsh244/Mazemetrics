#include "../include/grid.h"

void Grid::fill(const sf::Vector2u windowSize){
    blocks.reserve(rows * columns);

    float blockWidth = float(windowSize.x) / columns;
    float blockHeight = float(windowSize.y) / rows;
    sf::Color color = sf::Color::Red;

    for (int row = 0; row < rows; ++ row){
        for (int col = 0; col < columns; ++ col){
            Block block({blockWidth, blockHeight}, color);
            block.setPos({col * blockWidth, row * blockHeight});
            blocks.push_back(block);
        }
    }
}


void Grid::draw(sf::RenderWindow &win){
    for (auto& block:blocks){
        block.draw(win);
    }
}
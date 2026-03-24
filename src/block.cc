#include "../include/block.h"

Block::Block(sf::Vector2f size, Type blockType){
    shape.setSize(size);
    type = blockType;
    setColor();
}

void Block::setColor(){
    sf::Color color;
    if (type == OBSTACLE) color = COLOR::BLACK;
    else if (type == PATH) color = COLOR::YELLOW;
    else if (type == START) color = COLOR::GREEN;
    else if (type == END) color = COLOR::RED;
    else if (type == VISITED) color = COLOR::LBLUE;
    else if (type == UNVISITED) color = COLOR::GREY;
    shape.setFillColor(color);
}

void Block::draw(sf::RenderWindow &win){
    setColor();
    win.draw(shape);
}
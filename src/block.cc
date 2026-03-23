#include "../include/block.h"

Block::Block(sf::Vector2f size, sf::Color color){
    shape.setSize(size);
    shape.setFillColor(color);
}

void Block::draw(sf::RenderWindow &win){
    win.draw(shape);
}

void Block::setPos(sf::Vector2f position){
    shape.setPosition(position);
}
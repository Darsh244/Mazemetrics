#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class Type : int{
    VISITED,
    UNVISITED,
    WALL,
    PASSAGE
};

class Block {
    Type type;
    public:
        Block(Type blockType) : type(blockType) {}
        void setType(const Type blockType) {type = blockType;}
        Type getType() const {return type;}

};





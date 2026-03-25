#include <SFML/Graphics.hpp>
#include <iostream>

enum Type {
    OBSTACLE,
    PATH,
    START,
    END,
    VISITED,
    UNVISITED
};

class Block {
    Type type;
    public:
        Block(Type blockType) : type(blockType) {}
        void setType(Type blockType) {type = blockType;}
        Type getType() const {return type;}

};





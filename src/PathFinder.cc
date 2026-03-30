#include "../include/PathFinder.h"
#include "../include/Grid.h"
#include "../include/Position.h"
#include "Block.h"
#include <optional>

void PathFinder::setBlockType(Position blockPos, const Type type){
    grid.setBlockType(blockPos, type);
}

Type PathFinder::getBlockType(Position blockPos){
        return grid.getBlockType(blockPos);
}

bool PathFinder::outOfBounds(Position blockPos){
        return grid.outOfBounds(blockPos);
}

PathFinder::PathFinder(Grid& g) : grid(g) {
    start = std::nullopt;
    end = std::nullopt;
}

void PathFinder::setStartEnd(Position blockPos){
    Type type = getBlockType(blockPos);
    if (type == Type::VISITED || type == Type::PASSAGE){
        if (!start.has_value()){
            start = blockPos;
            setBlockType(start.value(), Type::START);
        }
        else if (!end.has_value()){
            end = blockPos;
            setBlockType(end.value(), Type::END);
        }
    }
}

void PathFinder::removeStartEnd(Position blockPos){
    if (getBlockType(blockPos) == Type::START) {
        setBlockType(start.value(), Type::VISITED);
        start = std::nullopt;
    }
    else if (getBlockType(blockPos) == Type::END){
        setBlockType(end.value(), Type::VISITED);
        end = std::nullopt;
    }
}
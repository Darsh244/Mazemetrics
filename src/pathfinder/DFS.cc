#include "pathfinder/DFS.h"
#include "core/Block.h"

void DFS::findPath(){
    Position starting_block;
    if (start.has_value()){
        starting_block = start.value();
    }
    addToStack(starting_block);
    seen.insert(starting_block);
    pathFindingStarted = true;
}

void DFS::findPathStep(int batchSize){
    for (int i = 0; i < batchSize; ++ i){
        if (!stack.empty() && !pathFound){
            Position current_block = getCurrentBlock();
            std::vector<Position> unexplored = exploreNeighbours(current_block);
            for (auto& block:unexplored){
                if (getBlockType(block) == Type::END){
                    currentPath = block;
                    pathFound = true;
                    break;
                }
                else {
                    markSeen(block);
                    addToStack(block);
                }
            }
        }
    }
}

void DFS::reconstructPathStep(int batchSize){
    for (int i = 0; i < batchSize; ++i){
        if (currentPath != start.value()){
            if (getBlockType(currentPath.value()) != Type::END) setBlockType(currentPath.value(), Type::PATH);
            Position nextPathPos = cameFrom[currentPath.value()];
            currentPath = nextPathPos;
        }
    }
}

std::vector<Position> DFS::exploreNeighbours(Position blockPos){
    int dr[] = {-1, 0, 1, 0}; // row offsets
    int dc[] = {0, 1, 0, -1}; // col offsets
    std::vector<int> indices = {0, 1, 2, 3};
    std::vector<Position> unexplored;
    for (int i:indices){
        Position neighbour = {blockPos.row + dr[i], blockPos.col + dc[i]};
        if (!seen.count(neighbour) && !outOfBounds(neighbour)){
            Type type = getBlockType(neighbour);
            if (type != Type::WALL){
                unexplored.push_back(neighbour);
                cameFrom[neighbour] = blockPos;
            }
        }
    }
    return unexplored;
}


Position DFS::getCurrentBlock(){
    Position pos = stack.back();
    stack.pop_back();
    return pos;
}


void DFS::addToStack(Position blockPos){
    stack.push_back(blockPos);
}

void DFS::markSeen(Position blockPos){
    seen.insert(blockPos);
    setBlockType(blockPos, Type::EXPLORED);
}
#include "pathfinder/BFS.h"
#include "core/Block.h"

void BFS::findPath(){
    Position starting_block;
    if (start.has_value()){
        starting_block = start.value();
    }
    addToQueue(starting_block);
    seen.insert(starting_block);
    pathFindingStarted = true;
}

void BFS::findPathStep(int batchSize){
    for (int i = 0; i < batchSize; ++ i){
        if (!queue.empty() && !pathFound){
            Position current_block = getCurrentBlock();
            std::vector<Position> unexplored = getNonExploredNeighbours(current_block);
            for (auto& block:unexplored){
                if (getBlockType(block) == Type::END){
                    currentPath = block;
                    pathFound = true;
                    break;
                }
                else {
                    markSeen(block);
                    addToQueue(block);
                }
            }
        }
    }
}

void BFS::reconstructPathStep(int batchSize){
    for (int i = 0; i < batchSize; ++i){
        if (currentPath != start.value()){
            if (getBlockType(currentPath.value()) != Type::END) setBlockType(currentPath.value(), Type::PATH);
            Position nextPathPos = cameFrom[currentPath.value()];
            currentPath = nextPathPos;
        }
    }
}

std::vector<Position> BFS::getNonExploredNeighbours(Position blockPos){
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


Position BFS::getCurrentBlock(){
    Position pos = queue.front();
    queue.pop();
    return pos;
}


void BFS::addToQueue(Position blockPos){
    queue.push(blockPos);
}

void BFS::markSeen(Position blockPos){
    seen.insert(blockPos);
    setBlockType(blockPos, Type::EXPLORED);
}
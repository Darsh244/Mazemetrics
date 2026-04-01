#include "../include/BFS.h"
#include "../include/Block.h"
#include "../include/Position.h"

#include <vector>


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
                    currentPathPos = block;
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
        if (currentPathPos != start.value()){
            if (getBlockType(currentPathPos) != Type::END) setBlockType(currentPathPos, Type::PATH);
            Position nextPathPos = parentMap[currentPathPos];
            currentPathPos = nextPathPos;
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
                parentMap[neighbour] = blockPos;
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
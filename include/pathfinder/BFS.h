#pragma once
#include "PathFinder.h"
#include <queue>
#include <unordered_set>
#include <vector>

struct Position;
class BFS : public PathFinder {

    std::queue<Position> queue;
    std::unordered_set<Position, Hasher> seen;

    public:
        BFS(Grid& g) : PathFinder(g) {};
        void findPath() override;
        void findPathStep(int batchSize = 1) override;
        void reconstructPathStep(int batchSize = 1) override;
    
    private:
        void addToQueue(Position blockPos);
        void markSeen(Position blockPos);
        Position getCurrentBlock();
        std::vector<Position> getNonExploredNeighbours(Position blockPos);

};
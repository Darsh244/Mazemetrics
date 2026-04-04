#pragma once
#include "PathFinder.h"
#include <unordered_set>
#include <vector>

struct Position;
class DFS : public PathFinder {

    std::vector<Position> stack;
    std::unordered_set<Position, Hasher> seen;

    public:
        DFS(Grid& g) : PathFinder(g) {};
        void findPath() override;
        void findPathStep(int batchSize = 1) override;
        void reconstructPathStep(int batchSize = 1) override;
    
    private:
        void addToStack(Position blockPos);
        void markSeen(Position blockPos);
        Position getCurrentBlock();
        std::vector<Position> exploreNeighbours(Position blockPos);

};
#pragma once
#include "PathFinder.h"
#include "Position.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Position;
class BFS : public PathFinder {
    struct Hasher {
        size_t operator() (const Position& p) const{
            size_t hash = p.row ^ (p.col << 1);
            return hash;
        }
    };
    
    std::queue<Position> queue;
    std::unordered_set<Position, Hasher> seen;
    std::unordered_map<Position, Position, Hasher> parentMap;
    Position currentPathPos;

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
#pragma once
#include "PathFinder.h"


class BFS : public PathFinder {

    public:
        BFS(Grid& g) : PathFinder(g) {}
        void findPath() override;
};
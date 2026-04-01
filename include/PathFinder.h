#pragma once
#include "Position.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

class Grid;
class Block;
enum class Type : int;


class PathFinder {
    protected:
        Grid& grid;
        std::optional<Position> start;
        std::optional<Position>  end;
        bool pathFound;
        bool pathFindingStarted;
        bool pathReconstructed;

        void setBlockType(Position blockPos, const Type type);
        Type getBlockType(Position blockPos);
        bool outOfBounds(Position blockPos);

        int getRows() const;
        int getColumns() const;

    public:
        PathFinder(Grid& g);

        virtual void findPath() = 0;
        virtual void findPathStep(int batchSize = 1) {}

        virtual void reconstructPathStep(int batchSize = 1) {}

        bool foundPath() {return pathFound;}
        bool pathFinderReady() {return start.has_value() && end.has_value();}
        bool pathFindingStart() {return pathFindingStarted;}
        bool isPathReconstructed() {return pathReconstructed;}

        void setStartEnd(Position blockPos);
        void removeStartEnd(Position blockPos);
        virtual ~PathFinder() {}
};
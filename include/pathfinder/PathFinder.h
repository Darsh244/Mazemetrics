#pragma once
#include "../core/Position.h"
#include <unordered_map>
#include <optional>

class Grid;
class Block;
enum class Type : int;


class PathFinder {
    protected:
        Grid& grid;
        std::optional<Position> start;
        std::optional<Position>  end;
        std::optional<Position> currentPath;
        std::unordered_map<Position, Position, Hasher> cameFrom;
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

        bool foundPath() const {return pathFound;}
        bool pathFinderReady() const {return start.has_value() && end.has_value();}
        bool pathFindingStart() const {return pathFindingStarted;}
        bool isPathReconstructed() const {return pathReconstructed;}

        void setStartEnd(Position blockPos);
        void removeStartEnd(Position blockPos);
        virtual ~PathFinder() {}
};
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

        void setBlockType(Position blockPos, const Type type);
        Type getBlockType(Position blockPos);
        bool outOfBounds(Position blockPos);

    public:
        PathFinder(Grid& g);
        virtual void findPath() = 0;
        void setStartEnd(Position blockPos);
        void removeStartEnd(Position blockPos);
        virtual ~PathFinder() {}
};
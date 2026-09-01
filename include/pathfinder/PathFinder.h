#pragma once
#include "../core/Position.h"
#include <optional>
#include <unordered_map>

class Grid;
class Block;
enum class Type : int;

class PathFinder {
protected:
  Grid &grid;
  std::optional<Position> start;
  std::optional<Position> end;
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

  void recordFrontierSize(int currentSize);

private:
  int pathLength = 0;
  int maxFrontierSize = 0;

public:
  PathFinder(Grid &g);

  virtual void findPath() = 0;
  virtual void findPathStep(int batchSize = 1) {}
  virtual void reconstructPathStep(int batchSize = 1) {}

  bool foundPath() const { return pathFound; }
  bool pathFinderReady() const { return start.has_value() && end.has_value(); }
  bool pathFindingStart() const { return pathFindingStarted; }
  bool isPathReconstructed() const { return pathReconstructed; }

  // Stats
  int getCellsVisited() const { return static_cast<int>(cameFrom.size()); }
  int getPathLength() const { return pathLength; }
  int getMaxFrontierSize() const { return maxFrontierSize; }

  // Fraction of visited cells that ended up on the final path
  double getPathEfficiencyPercent() const;

  void setStartEnd(Position blockPos);
  void removeStartEnd(Position blockPos);

  // Carries over start/end positions from another pathfinder instance
  void transferStartEnd(const PathFinder &other);

  // Repaints every EXPLORED/ACTIVE/PATH cell back to a walkable cell
  void clearSearchVisuals();

  virtual ~PathFinder() {}
};
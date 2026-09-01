#pragma once
#include "core/Grid.h"
#include "mazegen/MazeGenerator.h"
#include "pathfinder/PathFinder.h"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <memory>
#include <string>

enum class STATE {
  Start,
  GeneratingMaze,
  MazeGenerated,
  FindingPath,
  PathFound,
  ReconstructingPath,
  Finished
};

class MazeSimulator {
  Grid grid;
  std::unique_ptr<MazeGenerator> mazeGenerator;
  std::unique_ptr<PathFinder> pathFinder;

  sf::Vector2u window_size;
  std::string currentMazeGeneratorAlgorithm;
  std::string currentPathFinderAlgorithm;
  STATE state;

  int mazeGenerationSpeed;
  int pathFindingSpeed;
  int pathReconstructionSpeed;

  bool requestedWindowClose;
  unsigned uiSidebarWidth = 0; // pixels reserved to the left of the grid for UI
  unsigned uiStatsPanelWidth =
      0; // pixels reserved to the right of the grid for StatsPanel

  sf::Clock pathFindingClock;
  float pathFindingElapsedMs = 0.f; // keeps ticking while running
  std::unordered_map<std::string, std::function<void()>> mazeGeneratorMap;
  std::unordered_map<std::string, std::function<void()>> pathFinderMap;

public:
  MazeSimulator(sf::Vector2u grid_size);
  void initialize(sf::Vector2u size);
  void handleEvents(const sf::Event &event);
  void setUISidebarWidth(unsigned width) { uiSidebarWidth = width; }
  void setUIStatsPanelWidth(unsigned width) { uiStatsPanelWidth = width; }
  void runSimulation();
  bool shouldCloseWindow();

  void setMazeGenerationAlgorithm(const std::string &algorithm);
  void setPathFindingAlgorithm(const std::string &algorithm);
  const std::string &getCurrentPathFindingAlgorithm() const {
    return currentPathFinderAlgorithm;
  }
  bool canSwitchPathFindingAlgorithm() const;
  Grid &getGrid();

  void setMazeGenerationSpeed(int i) { mazeGenerationSpeed = i; }
  void setPathFindingSpeed(int i) { pathFindingSpeed = i; }
  void setPathReconstructionSpeed(int i) { pathReconstructionSpeed = i; }

  // Wipes everything and regenerates a brand new maze
  void resetMaze();

  // Clears only the pathfinding result
  void resetPath();

  // Stats for the sidebar readout
  int getCellsVisited() const {
    return pathFinder ? pathFinder->getCellsVisited() : 0;
  }
  int getPathLength() const {
    return pathFinder ? pathFinder->getPathLength() : 0;
  }
  int getMaxFrontierSize() const {
    return pathFinder ? pathFinder->getMaxFrontierSize() : 0;
  }
  double getPathEfficiencyPercent() const {
    return pathFinder ? pathFinder->getPathEfficiencyPercent() : 0.0;
  }
  float getPathFindingElapsedMs() const { return pathFindingElapsedMs; }

private:
  void initAlgorithmMaps();
};
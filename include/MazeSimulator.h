#pragma once
#include "core/Grid.h"
#include "mazegen/MazeGenerator.h"
#include "pathfinder/PathFinder.h"

#include <functional>
#include <memory>
#include <string>
#include <SFML/System/Vector2.hpp>

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

    bool requestedWindowClose;
    std::unordered_map<std::string, std::function<void()>> mazeGeneratorMap;
    std::unordered_map<std::string, std::function<void()>> pathFinderMap;
    public:
        MazeSimulator(sf::Vector2u grid_size);
        void initialize(sf::Vector2u size);
        void handleEvents(const sf::Event& event);
        void runSimulation(); 
        bool shouldCloseWindow();

        void setMazeGenerationAlgorithm(const std::string& algorithm);
        void setPathFindingAlgorithm(const std::string& algorithm);
        Grid& getGrid();
    
    private:
        void reset();
        void initAlgorithmMaps();


};
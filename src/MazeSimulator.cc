#include "MazeSimulator.h"
#include "mazegen/PrimGenerator.h"
#include "pathfinder/BFS.h"

MazeSimulator::MazeSimulator(sf::Vector2u grid_size) : grid(grid_size){
    requestedWindowClose = false;
    initAlgorithmMaps();
}

void MazeSimulator::initAlgorithmMaps(){
    mazeGeneratorMap["PRIM"] = [&]() {mazeGenerator = std::make_unique<PrimGenerator>(grid);};
    pathFinderMap["BFS"] = [&]() {pathFinder = std::make_unique<BFS>(grid);};
}


void MazeSimulator::initialize(sf::Vector2u size){
    window_size = size;
    grid.fill(window_size);
    state = STATE::Start;
}

void MazeSimulator::setMazeGenerationAlgorithm(const std::string& algorithm){
    mazeGeneratorMap[algorithm]();
    currentMazeGeneratorAlgorithm = algorithm;
}

void MazeSimulator::setPathFindingAlgorithm(const std::string& algorithm){
    pathFinderMap[algorithm]();
    currentPathFinderAlgorithm = algorithm;
}


void MazeSimulator::handleEvents(const sf::Event& event){
    if (event.is<sf::Event::Closed>()){
        requestedWindowClose = true;
    }
    else if (const auto* keypressed = event.getIf<sf::Event::KeyPressed>()){
        switch (keypressed->scancode){
            case sf::Keyboard::Scancode::Escape:
                requestedWindowClose = true;
                break;
            case sf::Keyboard::Scancode::R:
                reset();
                break;
            
            case sf::Keyboard::Scancode::Space:
                if (pathFinder->pathFinderReady() && !pathFinder->pathFindingStart()){
                    state = STATE::FindingPath;
                    pathFinder->findPath();
                }
                break;
            
            default:
                break;
        }
    }
    else if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()){
        if (mazeGenerator->generationDone()){
            // TODO - Fix weird stuff happening with large grid sizes when selecting start, end
            Position blockPos = {mouseButtonPressed->position.y, mouseButtonPressed->position.x};
            blockPos = blockPos / grid.getBlockSize(); // maps pixel position to row, col

            if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                pathFinder->setStartEnd(blockPos);
            }
            if (mouseButtonPressed->button == sf::Mouse::Button::Right){
                pathFinder->removeStartEnd(blockPos);
            }  
        }
    }

}

void MazeSimulator::reset(){
    grid.reset(window_size);
    mazeGeneratorMap[currentMazeGeneratorAlgorithm]();
    pathFinderMap[currentPathFinderAlgorithm]();
    state = STATE::Start;
    requestedWindowClose = false;
}


void MazeSimulator::runSimulation(){
    if (state == STATE::Start){
        mazeGenerator->generateMaze();
        state = STATE::GeneratingMaze;
    }
    if (state == STATE::GeneratingMaze){
        mazeGenerator->generateMazeStep(10);
        if (mazeGenerator->generationDone()) state = STATE::MazeGenerated;
    }
    if (state == STATE::FindingPath){
        pathFinder->findPathStep(5);
        if (pathFinder->foundPath()) state = STATE::PathFound;
    }
    if (state == STATE::PathFound){
        pathFinder->reconstructPathStep(2);
        if (pathFinder->isPathReconstructed()) state = STATE::Finished;
    }
}


Grid& MazeSimulator::getGrid(){
    return grid;
}

bool MazeSimulator::shouldCloseWindow(){
    return requestedWindowClose;
}

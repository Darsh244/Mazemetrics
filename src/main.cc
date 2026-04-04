#include "renderer/Renderer.h"
#include "MazeSimulator.h"
#include <memory>

constexpr unsigned WINDOW_HEIGHT = 1600;
constexpr unsigned WINDOW_WIDTH = 1600;

int main(){
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Window");
    window.setFramerateLimit(60);

    MazeSimulator simulator({60, 60});
    simulator.initialize(window.getSize());
    simulator.setMazeGenerationAlgorithm("PRIM");
    simulator.setPathFindingAlgorithm("DFS");

    simulator.setMazeGenerationSpeed(100);
    simulator.setPathFindingSpeed(20);
    simulator.setPathReconstructionSpeed(10);

    while (window.isOpen()){
        while (const auto event = window.pollEvent()){
            simulator.handleEvents(event.value());
            if (simulator.shouldCloseWindow()) window.close();
        }
        window.clear(sf::Color(240, 240, 240));

        simulator.runSimulation();

        Renderer::draw(window, simulator.getGrid());
        window.display();
    }
}

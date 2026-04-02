#include "renderer/Renderer.h"
#include "MazeSimulator.h"
#include <memory>

constexpr unsigned WINDOW_HEIGHT = 800;
constexpr unsigned WINDOW_WIDTH = 800;

int main(){
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Window");
    window.setFramerateLimit(60);

    MazeSimulator simulator({10, 10});
    simulator.initialize(window.getSize());
    simulator.setMazeGenerationAlgorithm("PRIM");
    simulator.setPathFindingAlgorithm("BFS");

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

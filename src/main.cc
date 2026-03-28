#include "../include/Grid.h"
#include "../include/PrimGenerator.h"
#include "MazeGenerator.h"
#include "Position.h"
#include <algorithm>
#include <memory>
#include <random>

constexpr unsigned WINDOW_HEIGHT = 800;
constexpr unsigned WINDOW_WIDTH = 800;

int main(){
    sf::RenderWindow window;
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Window");
    window.setFramerateLimit(20);

    Grid grid(10, 10); 
    grid.fill(window.getSize());
    std::unique_ptr<PrimGenerator> mazeGenerator = std::make_unique<PrimGenerator>(grid);
    mazeGenerator->generateMaze();
    
    
    while (window.isOpen()){
        while (const auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            else if (const auto* keypressed = event->getIf<sf::Event::KeyPressed>()){
                if (keypressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                }
                if (keypressed->scancode == sf::Keyboard::Scancode::R){
                    grid.reset(window.getSize());
                    mazeGenerator = std::make_unique<PrimGenerator>(grid);
                    mazeGenerator->generateMaze();
                }
            }

        }

        window.clear(sf::Color(240, 240, 240));
        if (!mazeGenerator->generationDone()){
            mazeGenerator->generateMazeStep(1);
        }
        grid.draw(window);
        window.display();
    }
}

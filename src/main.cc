#include "../include/Grid.h"
#include "../include/PrimGenerator.h"
#include "../include/MazeGenerator.h"
#include "../include/PathFinder.h"
#include "../include/BFS.h"
#include "../include/Position.h"
#include <algorithm>
#include <memory>
#include <random>

constexpr unsigned WINDOW_HEIGHT = 800;
constexpr unsigned WINDOW_WIDTH = 800;

int main(){
    sf::RenderWindow window;
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Window");
    window.setFramerateLimit(60);

    Grid grid(10, 10); 
    grid.fill(window.getSize());
    std::unique_ptr<MazeGenerator> mazeGenerator = std::make_unique<PrimGenerator>(grid);
    std::unique_ptr<PathFinder> pathFinder = std::make_unique<BFS>(grid);
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
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mazeGenerator->generationDone()){
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

        window.clear(sf::Color(240, 240, 240));
        if (!mazeGenerator->generationDone()){
            mazeGenerator->generateMazeStep(2);
        }
        grid.draw(window);
        window.display();
    }
}

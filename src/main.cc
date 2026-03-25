#include "../include/grid.h"
#include <random>

constexpr unsigned WINDOW_HEIGHT = 800;
constexpr unsigned WINDOW_WIDTH = 800;

int main(){
    sf::RenderWindow window;
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Window");
    window.setFramerateLimit(60);

    Grid grid(75, 75); 
    grid.fill(window.getSize());

    while (window.isOpen()){
        while (const auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            else if (const auto* keypressed = event->getIf<sf::Event::KeyPressed>()){
                if (keypressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                }
            }

        }

        window.clear(sf::Color(240, 240, 240));

        grid.draw(window);
        if (!grid.generationDone()){
            grid.generateMaze();
        }
        window.display();
    }
}

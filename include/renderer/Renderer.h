#include <SFML/Graphics.hpp>

class Grid;


namespace COLOR {
    const sf::Color RED(255, 0, 0);
    const sf::Color GREEN(0, 255, 0);
    const sf::Color LBLUE(173, 216, 230);
    const sf::Color LGREY(245, 245, 245);
    const sf::Color BLACK(0, 0, 0);
    const sf::Color GOLD (255, 215, 0);
    const sf::Color WHITE(255, 255, 255);

};

class Renderer {
    public:
        Renderer() = delete;
        static void draw(sf::RenderWindow& win, Grid& grid);
};
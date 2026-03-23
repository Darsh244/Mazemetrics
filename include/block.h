#include <SFML/Graphics.hpp>

class Block {
    sf::RectangleShape shape;
    public:
        Block(sf::Vector2f size, sf::Color color);
        void draw(sf::RenderWindow& win);
        void setPos(sf::Vector2f position);
};





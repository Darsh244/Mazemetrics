#include <SFML/Graphics.hpp>

enum Type {
    OBSTACLE,
    PATH,
    START,
    END,
    VISITED,
    UNVISITED
};

namespace COLOR {
    const sf::Color RED(255, 0, 0);
    const sf::Color GREEN(0, 255, 0);
    const sf::Color LBLUE(173, 216, 230);
    const sf::Color GREY(128, 128, 128);
    const sf::Color BLACK(0, 0, 0);
    const sf::Color YELLOW(255, 255, 0);
    const sf::Color WHITE(255, 255, 255);

}

class Block {
    sf::RectangleShape shape;
    Type type;
    public:
        Block(sf::Vector2f size, Type blockType);
        void setPos(sf::Vector2f position) {shape.setPosition(position);}
        void setType(Type blockType) {type = blockType;}

        void draw(sf::RenderWindow& win);
        void setColor();
};





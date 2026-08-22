#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class Button {
  sf::RectangleShape shape;
  sf::Text label;
  std::function<void()> onClick;
  bool active; // currently selected algorithm
  bool hovered;

public:
  Button(sf::Font &font, const std::string &text, sf::Vector2f position,
         sf::Vector2f size, std::function<void()> callback);

  void handleEvent(const sf::Event &event);
  void draw(sf::RenderWindow &window);

  void setActive(bool isActive);
  bool isActive() const { return active; }

  bool contains(sf::Vector2f point) const;

private:
  void updateColors();
};
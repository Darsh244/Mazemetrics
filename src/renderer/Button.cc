#include "renderer/Button.h"
#include "renderer/Renderer.h"

Button::Button(sf::Font &font, const std::string &text, sf::Vector2f position,
               sf::Vector2f size, std::function<void()> callback)
    : label(font, text, 18), onClick(callback), active(false), hovered(false) {
  shape.setPosition(position);
  shape.setSize(size);
  shape.setOutlineThickness(1.f);

  label.setFillColor(COLOR::BLACK);
  // center the label within the button
  sf::FloatRect bounds = label.getLocalBounds();
  label.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                   bounds.position.y + bounds.size.y / 2.f});
  label.setPosition({position.x + size.x / 2.f, position.y + size.y / 2.f});

  updateColors();
}

void Button::setActive(bool isActive) {
  if (active != isActive) {
    active = isActive;
    updateColors();
  }
}

void Button::updateColors() {
  if (active) {
    shape.setFillColor(COLOR::GOLD);
    shape.setOutlineColor(COLOR::BLACK);
  } else if (hovered) {
    shape.setFillColor(COLOR::LBLUE);
    shape.setOutlineColor(COLOR::BLACK);
  } else {
    shape.setFillColor(COLOR::WHITE);
    shape.setOutlineColor(COLOR::BLACK);
  }
}

bool Button::contains(sf::Vector2f point) const {
  return shape.getGlobalBounds().contains(point);
}

void Button::handleEvent(const sf::Event &event) {
  if (const auto *moved = event.getIf<sf::Event::MouseMoved>()) {
    sf::Vector2f mousePos(float(moved->position.x), float(moved->position.y));
    bool nowHovered = contains(mousePos);
    if (nowHovered != hovered) {
      hovered = nowHovered;
      updateColors();
    }
  } else if (const auto *pressed =
                 event.getIf<sf::Event::MouseButtonPressed>()) {
    if (pressed->button == sf::Mouse::Button::Left) {
      sf::Vector2f mousePos(float(pressed->position.x),
                            float(pressed->position.y));
      if (contains(mousePos) && onClick) {
        onClick();
      }
    }
  }
}

void Button::draw(sf::RenderWindow &window) {
  window.draw(shape);
  window.draw(label);
}
#pragma once
#include "renderer/Button.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>

// A single labeled group of buttons within the sidebar
struct SidebarSection {
  std::string title;
  std::vector<std::string> optionNames;
  std::function<void(const std::string &)> onSelect;
  std::string initialActive;
};

// Vertical sidebar with labeled sections of buttons
class Sidebar {
  sf::Font font;
  sf::RectangleShape background;
  float width;

  struct RenderedSection {
    std::string title;
    sf::Text titleText;
    std::vector<std::string> names;
    std::vector<Button> buttons;
  };
  std::vector<RenderedSection> sections;

public:
  Sidebar(const std::string &fontPath, float width, float height,
          const std::vector<SidebarSection> &sectionDefs);

  void handleEvent(const sf::Event &event);
  void draw(sf::RenderWindow &window);

  // Updates which button is highlighted active within a given section.
  void setActiveOption(const std::string &sectionTitle,
                       const std::string &optionName);

  float getWidth() const { return width; }
};
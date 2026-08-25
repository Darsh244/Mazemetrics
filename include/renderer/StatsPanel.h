#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct StatEntry {
  std::string label;
  std::string value;
};

class StatsPanel {
  sf::Font font;
  sf::RectangleShape background;
  sf::Text titleText;
  float width;

  struct RenderedStat {
    sf::Text labelText;
    sf::Text valueText;
  };
  std::vector<RenderedStat> rows;
  std::vector<std::string> rowLabels; // tracks label -> row index

public:
  StatsPanel(const std::string &fontPath, float xPosition, float width,
             float height, const std::vector<StatEntry> &initialStats);

  // Updates values in place
  void setStats(const std::vector<StatEntry> &stats);

  void draw(sf::RenderWindow &window);

  float getWidth() const { return width; }
};
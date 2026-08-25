#include "renderer/StatsPanel.h"
#include "renderer/Renderer.h"
#include <algorithm>
#include <stdexcept>

StatsPanel::StatsPanel(const std::string &fontPath, float xPosition,
                       float width, float height,
                       const std::vector<StatEntry> &initialStats)
    : width(width), titleText(font, "Statistics", 14) {
  if (!font.openFromFile(fontPath)) {
    throw std::runtime_error("StatsPanel: failed to load font at " + fontPath);
  }

  background.setPosition({xPosition, 0.f});
  background.setSize({width, height});
  background.setFillColor(COLOR::LGREY);

  float padding = 16.f;
  float rowHeight = 44.f;

  titleText.setFillColor(COLOR::BLACK);
  titleText.setPosition({xPosition + padding, padding});

  float y = padding + 30.f;
  for (const auto &stat : initialStats) {
    RenderedStat row{sf::Text(font, stat.label, 12),
                     sf::Text(font, stat.value, 20)};
    row.labelText.setFillColor(COLOR::BLACK);
    row.labelText.setPosition({xPosition + padding, y});

    row.valueText.setFillColor(COLOR::BLACK);
    row.valueText.setPosition({xPosition + padding, y + 16.f});

    rows.push_back(std::move(row));
    rowLabels.push_back(stat.label);

    y += rowHeight;
  }
}

void StatsPanel::setStats(const std::vector<StatEntry> &stats) {
  for (const auto &stat : stats) {
    auto it = std::find(rowLabels.begin(), rowLabels.end(), stat.label);
    if (it == rowLabels.end())
      continue; // unknown label, ignore
    size_t index = std::distance(rowLabels.begin(), it);
    rows[index].valueText.setString(stat.value);
  }
}

void StatsPanel::draw(sf::RenderWindow &window) {
  window.draw(background);
  window.draw(titleText);
  for (auto &row : rows) {
    window.draw(row.labelText);
    window.draw(row.valueText);
  }
}
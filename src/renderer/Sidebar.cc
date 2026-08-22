#include "renderer/Sidebar.h"
#include "renderer/Renderer.h"
#include <stdexcept>

Sidebar::Sidebar(const std::string &fontPath, float width, float height,
                 const std::vector<SidebarSection> &sectionDefs)
    : width(width) {
  if (!font.openFromFile(fontPath)) {
    throw std::runtime_error("Sidebar: failed to load font at " + fontPath);
  }

  background.setPosition({0.f, 0.f});
  background.setSize({width, height});
  background.setFillColor(COLOR::LGREY);

  float padding = 16.f;
  float sectionGap = 20.f;
  float titleHeight = 22.f;
  float buttonHeight = 36.f;
  float buttonGap = 6.f;
  float buttonWidth = width - 2.f * padding;

  float y = padding;

  for (const auto &def : sectionDefs) {
    RenderedSection section{
        def.title, sf::Text(font, def.title, 14), def.optionNames, {}};
    section.titleText.setFillColor(COLOR::BLACK);
    section.titleText.setPosition({padding, y});
    y += titleHeight;

    for (const auto &name : def.optionNames) {
      section.buttons.emplace_back(
          font, name, sf::Vector2f(padding, y),
          sf::Vector2f(buttonWidth, buttonHeight),
          [name, callback = def.onSelect]() { callback(name); });
      y += buttonHeight + buttonGap;
    }

    sections.push_back(std::move(section));
    y += sectionGap;

    setActiveOption(def.title, def.initialActive);
  }
}

void Sidebar::setActiveOption(const std::string &sectionTitle,
                              const std::string &optionName) {
  for (auto &section : sections) {
    if (section.title != sectionTitle)
      continue;
    for (size_t i = 0; i < section.names.size(); ++i) {
      section.buttons[i].setActive(section.names[i] == optionName);
    }
  }
}

void Sidebar::handleEvent(const sf::Event &event) {
  for (auto &section : sections) {
    for (auto &button : section.buttons) {
      button.handleEvent(event);
    }
  }
}

void Sidebar::draw(sf::RenderWindow &window) {
  window.draw(background);
  for (auto &section : sections) {
    window.draw(section.titleText);
    for (auto &button : section.buttons) {
      button.draw(window);
    }
  }
}
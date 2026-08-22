#include "MazeSimulator.h"
#include "renderer/Renderer.h"
#include "renderer/Sidebar.h"
#include <memory>
#include <string>

constexpr unsigned WINDOW_HEIGHT = 1600;
constexpr unsigned WINDOW_WIDTH = 1600;
constexpr float SIDEBAR_WIDTH = 220.f;

const std::string FONT_PATH =
    std::string(PROJECT_ROOT) + "/asset/fonts/font.ttf";

int main() {
  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                          "Window");
  window.setFramerateLimit(60);

  MazeSimulator simulator({60, 60});

  // reserve pixels on the left of the window for the UI sidebar
  sf::Vector2u playableArea = window.getSize();
  playableArea.x -= static_cast<unsigned>(SIDEBAR_WIDTH);

  simulator.initialize(playableArea);
  simulator.setUISidebarWidth(static_cast<unsigned>(SIDEBAR_WIDTH));
  simulator.setMazeGenerationAlgorithm("PRIM");
  simulator.setPathFindingAlgorithm("DFS");
  simulator.setMazeGenerationSpeed(100);
  simulator.setPathFindingSpeed(20);
  simulator.setPathReconstructionSpeed(10);

  Sidebar sidebar(FONT_PATH, SIDEBAR_WIDTH, float(WINDOW_HEIGHT),
                  {SidebarSection{"Path finding",
                                  {"BFS", "DFS"},
                                  [&simulator](const std::string &name) {
                                    simulator.setPathFindingAlgorithm(name);
                                  },
                                  simulator.getCurrentPathFindingAlgorithm()}});

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      simulator.handleEvents(event.value());
      sidebar.handleEvent(event.value());
      if (simulator.shouldCloseWindow())
        window.close();
    }

    sidebar.setActiveOption("Path finding",
                            simulator.getCurrentPathFindingAlgorithm());

    window.clear(sf::Color(240, 240, 240));
    simulator.runSimulation();
    Renderer::draw(window, simulator.getGrid(), SIDEBAR_WIDTH);
    sidebar.draw(window);
    window.display();
  }
}
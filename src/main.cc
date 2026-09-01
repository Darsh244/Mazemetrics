#include "MazeSimulator.h"
#include "renderer/Renderer.h"
#include "renderer/Sidebar.h"
#include "renderer/StatsPanel.h"
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

constexpr unsigned WINDOW_HEIGHT = 1600;
constexpr unsigned WINDOW_WIDTH = 1600;
constexpr float SIDEBAR_WIDTH = 220.f;
constexpr float STATS_PANEL_WIDTH = 220.f;

const std::string FONT_PATH =
    std::string(PROJECT_ROOT) + "/asset/fonts/font.ttf";

std::string formatMs(float ms) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(0) << ms << " ms";
  return oss.str();
}

std::string formatPercent(double percent) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(1) << percent << "%";
  return oss.str();
}

int main() {
  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                          "Window");
  window.setFramerateLimit(60);

  MazeSimulator simulator({60, 60});

  // reserve SIDEBAR_WIDTH on the left and STATS_PANEL_WIDTH on the right for UI
  sf::Vector2u playableArea = window.getSize();
  playableArea.x -= static_cast<unsigned>(SIDEBAR_WIDTH + STATS_PANEL_WIDTH);

  simulator.initialize(playableArea);
  simulator.setUISidebarWidth(static_cast<unsigned>(SIDEBAR_WIDTH));
  simulator.setUIStatsPanelWidth(static_cast<unsigned>(STATS_PANEL_WIDTH));
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

  StatsPanel statsPanel(FONT_PATH, float(WINDOW_WIDTH) - STATS_PANEL_WIDTH,
                        STATS_PANEL_WIDTH, float(WINDOW_HEIGHT),
                        {{"Time", "0 ms"},
                         {"Cells visited", "0"},
                         {"Path length", "0"},
                         {"Path efficiency", "0.0%"},
                         {"Max frontier size", "0"}});

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      simulator.handleEvents(event.value());
      sidebar.handleEvent(event.value());
      if (simulator.shouldCloseWindow())
        window.close();
    }

    sidebar.setActiveOption("Path finding",
                            simulator.getCurrentPathFindingAlgorithm());

    statsPanel.setStats(
        {{"Time", formatMs(simulator.getPathFindingElapsedMs())},
         {"Cells visited", std::to_string(simulator.getCellsVisited())},
         {"Path length", std::to_string(simulator.getPathLength())},
         {"Path efficiency",
          formatPercent(simulator.getPathEfficiencyPercent())},
         {"Max frontier size",
          std::to_string(simulator.getMaxFrontierSize())}});

    window.clear(sf::Color(240, 240, 240));
    simulator.runSimulation();
    Renderer::draw(window, simulator.getGrid(), SIDEBAR_WIDTH);
    sidebar.draw(window);
    statsPanel.draw(window);
    window.display();
  }
}
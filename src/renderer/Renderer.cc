#include "renderer/Renderer.h"
#include "core/Grid.h"

void Renderer::draw(sf::RenderWindow &win, Grid &grid, float xOffset) {
  sf::RenderStates states;
  states.transform.translate({xOffset, 0.f});
  win.draw(grid.getVertexArray(), states);
}
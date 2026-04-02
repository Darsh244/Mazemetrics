#include "renderer/Renderer.h"
#include "core/Grid.h"

void Renderer::draw(sf::RenderWindow& win, Grid &grid){
    win.draw(grid.getVertexArray());
}
#ifndef GRID_H
#define GRID_H

#include "globals.h"
#include "minesweeper/cell.h"
#include <vector>

class MineSweeperGrid {
public:
  MineSweeperGrid(int x, int y) {
    using namespace Config;
    for (int col{1}; col <= GRID_COLUMNS; ++col) {
      for (int row{1}; row <= GRID_ROWS; ++row) {
        constexpr int spacing{CELL_SIZE + PADDING};

        children.emplace_back(x + (spacing) * (col - 1),
                              y + (spacing) * (row - 1), CELL_SIZE, CELL_SIZE,
                              row, col);
      }
    }
  }

  void render(SDL_Surface *surface) {
    for (auto &child : children) {
      child.render(surface);
    }
  }

  void handleEvent(const SDL_Event &event) {
    for (auto &child : children) {
      child.handleEvent(event);
    }
  }

  std::vector<MineSweeperCell> children;
};

#endif // !GRID_H

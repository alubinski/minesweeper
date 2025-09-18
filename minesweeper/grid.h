#ifndef GRID_H
#define GRID_H

#include "engine/random.h"
#include "globals.h"
#include "minesweeper/cell.h"
#include <SDL2/SDL.h>
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
    placeBombs();
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

private:
  void placeBombs() {
    int bombtoPlace{Config::BOMB_COUNT};
    while (bombtoPlace > 0) {
      const size_t randomIndex{Engine::Random::Int(0, children.size() - 1)};
      if (children[randomIndex].placeBomb()) {
        --bombtoPlace;
      }
    }
  }
};

#endif // !GRID_H

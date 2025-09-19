#ifndef GRID_H
#define GRID_H

#include "engine/random.h"
#include "globals.h"
#include "minesweeper/cell.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
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
    if (event.type == UserEvents::CELL_CLEARED) {
      handleCellCleared(event.user);
    } else if (event.type == UserEvents::NEW_GAME) {
      for (auto &child : children) {
        child.reset();
      }
      placeBombs();
    }

    for (auto &child : children) {
      child.handleEvent(event);
    }
  }

private:
  void placeBombs() {
    cellsToClear_ =
        Config::GRID_COLUMNS * Config::GRID_ROWS - Config::BOMB_COUNT;
    int bombtoPlace{Config::BOMB_COUNT};
    while (bombtoPlace > 0) {
      const size_t randomIndex{Engine::Random::Int(0, children.size() - 1)};
      if (children[randomIndex].placeBomb()) {
        --bombtoPlace;
      }
    }
  }

  void handleCellCleared(const SDL_UserEvent &event) {
    auto *cell = static_cast<MineSweeperCell *>(event.data1);

    if (cell->hasBomb()) {
      SDL_Event loseEvent{UserEvents::GAME_LOST};
      SDL_PushEvent(&loseEvent);
    } else {
      --cellsToClear_;
      if (cellsToClear_ == 0) {
        SDL_Event winEvent{UserEvents::GAME_WON};
        SDL_PushEvent(&winEvent);
      }
    }
  }

  std::vector<MineSweeperCell> children;
  int cellsToClear_;
};

#endif // !GRID_H

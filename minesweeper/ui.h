#ifndef UI_H
#define UI_H

#include "globals.h"
#include "minesweeper/flag_counter.h"
#include "minesweeper/grid.h"
#include "minesweeper/new_game_button.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
class MinesweeperUI {
public:
  void render(SDL_Surface *surface) {
    grid_.render(surface);
    newGameButton_.render(surface);
    flagCounter_.render(surface);
  }
  void handleEvent(const SDL_Event &e) {
    grid_.handleEvent(e);
    newGameButton_.handleEvent(e);
    flagCounter_.handleEvent(e);
  }

private:
  MineSweeperGrid grid_{Config::PADDING, Config::PADDING};
  NewGameButton newGameButton_{
      Config::PADDING, Config::GRID_HEIGHT + Config::PADDING * 2,
      Config::WINDOW_WIDTH - Config::PADDING * 3 - Config::FLAG_COUNTER_WIDTH,
      Config::FOOTER_HEIGHT - Config::PADDING};
  FlagCounter flagCounter_{
      Config::WINDOW_WIDTH - Config::FLAG_COUNTER_WIDTH - Config::PADDING,
      Config::GRID_HEIGHT + Config::PADDING * 2, Config::FLAG_COUNTER_WIDTH,
      Config::FOOTER_HEIGHT - Config::PADDING};
};

#endif

#ifndef UI_H
#define UI_H

#include "minesweeper/grid.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
class MinesweeperUI {
public:
  void render(SDL_Surface *surface) { grid.render(surface); }
  void handleEvent(const SDL_Event &e) { grid.handleEvent(e); }

private:
  MineSweeperGrid grid{Config::PADDING, Config::PADDING};
};

#endif

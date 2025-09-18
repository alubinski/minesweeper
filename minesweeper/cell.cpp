#include "cell.h"
#include "globals.h"
#include <cstdint>

MineSweeperCell::MineSweeperCell(int x, int y, int w, int h, int row, int col)
    : Button{x, y, w, h}, row_{row}, col_{col} {};

void MineSweeperCell::handleEvent(const SDL_Event &event) {
  if (event.type == UserEvents::CELL_CLEARED) {
    std::cout << "A cell was cleared!" << std::endl;
  }
  Button::handleEvent(event);
}

void MineSweeperCell::render(SDL_Surface *surface) { Button::render(surface); }

void MineSweeperCell::clearCell() {
  if (isCleared_) {
    return;
  }
  isCleared_ = true;
  setIsDisabled(true);
  setColor(Config::BUTTON_CLEARED_COLOR);
  reportEvent(UserEvents::CELL_CLEARED);
}

void MineSweeperCell::handleLeftClick() { clearCell(); }

void MineSweeperCell::reportEvent(uint32_t eventType) {
  SDL_Event event{eventType};
  event.user.data1 = this;
  SDL_PushEvent(&event);
}

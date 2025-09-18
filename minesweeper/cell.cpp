#include "cell.h"
#include "globals.h"
#include <cstdint>

MineSweeperCell::MineSweeperCell(int x, int y, int w, int h, int row, int col)
    : Button{x, y, w, h}, row_{row}, col_{col},
      bombImage_{x, y, w, h, Config::BOMB_IMAGE} {};

void MineSweeperCell::handleEvent(const SDL_Event &event) {
  if (event.type == UserEvents::CELL_CLEARED) {
    std::cout << "A cell was cleared!" << std::endl;
  } else if (event.type == UserEvents::BOMB_PLACED) {
    std::cout << "A bomb was placed!" << std::endl;
  }
  Button::handleEvent(event);
}

void MineSweeperCell::render(SDL_Surface *surface) {
  Button::render(surface);
  if (isCleared_ && hasBomb_) {
    bombImage_.render(surface);
  }
#ifdef SHOW_DEBUG_INFO
  else if (hasBomb_) {
    bombImage_.render(surface);
  }
#endif
}

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

bool MineSweeperCell::placeBomb() {
  if (hasBomb_) {
    return false;
  }
  hasBomb_ = true;
  reportEvent(UserEvents::BOMB_PLACED);
  return true;
}

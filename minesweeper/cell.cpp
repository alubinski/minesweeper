#include "cell.h"
#include "globals.h"
#include <cstdint>
#include <string>

MineSweeperCell::MineSweeperCell(int x, int y, int w, int h, int row, int col)
    : Button{x, y, w, h}, row_{row}, col_{col},
      bombImage_{x, y, w, h, Config::BOMB_IMAGE},
      flagImage_{x, y, w, h, Config::FLAG_IMAGE},
      text_{x,
            y,
            w,
            h,
            std::to_string(adjacentBombs_),
            Config::TEXT_COLORS[adjacentBombs_]} {};

void MineSweeperCell::handleEvent(const SDL_Event &event) {
  if (event.type == UserEvents::CELL_CLEARED) {
    handleCellCleared(event.user);
  } else if (event.type == UserEvents::BOMB_PLACED) {
    hableBombPlaced(event.user);
  } else if (event.type == UserEvents::GAME_WON) {
    if (hasBomb()) {
      hasFlag_ = hasBomb_;
      setColor(Config::BUTTON_SUCCESS_COLOR);
    }
    setIsDisabled(true);
  } else if (event.type == UserEvents::GAME_LOST) {
    if (hasBomb()) {
      isCleared_ = true;
      setColor(Config::BUTTON_FAILURE_COLOR);
    }
    setIsDisabled(true);
  }
  Button::handleEvent(event);
}

void MineSweeperCell::render(SDL_Surface *surface) {
  Button::render(surface);
  if (hasFlag_) {
    flagImage_.render(surface);
  } else if (isCleared_ && hasBomb_) {
    bombImage_.render(surface);
  } else if (isCleared_ && adjacentBombs_ > 0) {
    text_.render(surface);
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

void MineSweeperCell::handleLeftClick() {
  if (!hasFlag_)
    clearCell();
}

void MineSweeperCell::handleRightClick() {
  if (hasFlag_) {
    reportEvent(UserEvents::FLAG_CLEARED);
    hasFlag_ = false;
  } else {
    reportEvent(UserEvents::FLAG_PLACED);
    hasFlag_ = true;
  }
}

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

bool MineSweeperCell::isAdjacent(MineSweeperCell *other) const {
  return !(other == this) && std::abs(getRow() - other->getRow()) <= 1 &&
         std::abs(getCol() - other->getCol()) <= 1;
}

void MineSweeperCell::hableBombPlaced(const SDL_UserEvent &event) {
  auto *other = static_cast<MineSweeperCell *>(event.data1);
  if (isAdjacent(other)) {
    ++adjacentBombs_;
    text_.setText(std::to_string(adjacentBombs_),
                  Config::TEXT_COLORS[adjacentBombs_]);
  }
}

void MineSweeperCell::handleCellCleared(const SDL_UserEvent &event) {
  auto *other = static_cast<MineSweeperCell *>(event.data1);

  if (other->hasBomb())
    return;

  if (isAdjacent(other) && other->adjacentBombs_ == 0) {
    clearCell();
  }
}

void MineSweeperCell::reset() {
  isCleared_ = false;
  hasFlag_ = false;
  hasBomb_ = false;
  adjacentBombs_ = 0;
  setIsDisabled(false);
  setColor(Config::BUTTON_COLOR);
}

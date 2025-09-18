#ifndef CELL_H
#define CELL_H

#include "engine/button.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>

class MineSweeperCell : public Engine::Button {
public:
  MineSweeperCell(int x, int y, int w, int h, int row, int col);

  void handleEvent(const SDL_Event &event) override;
  void render(SDL_Surface *surface) override;

  [[nodiscard]]
  int getRow() const {
    return row_;
  }

  [[nodiscard]]
  int getCol() const {
    return col_;
  }

protected:
  void handleLeftClick() override;

private:
  void clearCell();
  void reportEvent(uint32_t eventType);
  bool isCleared_{false};
  int row_;
  int col_;
};

#endif // CELL_H

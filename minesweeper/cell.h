#ifndef CELL_H
#define CELL_H

#include "engine/button.h"
#include "engine/image.h"
#include "engine/text.h"
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

  bool placeBomb();

  [[nodiscard]]
  bool hasBomb() const {
    return hasBomb_;
  }

  void reset();

protected:
  void handleLeftClick() override;
  void handleRightClick() override;

private:
  void clearCell();
  void reportEvent(uint32_t eventType);
  bool isAdjacent(MineSweeperCell *other) const;
  void hableBombPlaced(const SDL_UserEvent &event);
  void handleCellCleared(const SDL_UserEvent &event);
  bool isCleared_{false};
  int row_;
  int col_;
  bool hasBomb_{false};
  int adjacentBombs_{0};
  bool hasFlag_{false};
  Engine::Image bombImage_;
  Engine::Image flagImage_;
  Engine::Text text_;
};

#endif // CELL_H

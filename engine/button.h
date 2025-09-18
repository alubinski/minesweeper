#ifndef BUTTON_H
#define BUTTON_H

#include "engine/rectangle.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

namespace Engine {
class Button : public Rectangle {
public:
  Button(int x, int y, int w, int h) : Rectangle(x, y, w, h) {
    setColor(Config::BUTTON_COLOR);
  }

  virtual void handleEvent(const SDL_Event &e) {
    if (isDisabled_)
      return;
    if (e.type == SDL_MOUSEMOTION) {
      handleMouseMotion(e.motion);
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      if (isWithinBounds(e.button.x, e.button.y)) {
        e.button.button == SDL_BUTTON_LEFT ? handleLeftClick()
                                           : handleRightClick();
      }
    }
  }

  void setIsDisabled(bool newValue) { isDisabled_ = newValue; }

protected:
  virtual void handleLeftClick() {}
  virtual void handleRightClick() {}

  virtual void handleMouseMotion(const SDL_MouseMotionEvent &e) {
    if (isWithinBounds(e.x, e.y)) {
      setColor(Config::BUTTON_HOVER_COLOR);
    } else {
      setColor(Config::BUTTON_COLOR);
    }
  }

private:
  bool isDisabled_{false};
};
} // namespace Engine

#endif

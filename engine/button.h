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
    setColor(Config::c_buttonColor);
  }

  virtual void handleEvents(const SDL_Event &e) {
    if (m_isDisabled)
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

  void setIsDisabled(bool newValue) { m_isDisabled = newValue; }

protected:
  virtual void handleLeftClick() {}
  virtual void handleRightClick() {}

  virtual void handleMouseMotion(const SDL_MouseMotionEvent &e) {
    if (isWithinBounds(e.x, e.y)) {
      setColor(Config::c_buttonHoverColor);
    } else {
      setColor(Config::c_buttonColor);
    }
  }

private:
  bool m_isDisabled{false};
};
} // namespace Engine

#endif

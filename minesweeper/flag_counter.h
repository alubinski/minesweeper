#ifndef FLAG_COUNTER_H
#define FLAG_COUNTER_H

#include "engine/image.h"
#include "engine/rectangle.h"
#include "engine/text.h"
#include "globals.h"
#include <string>

class FlagCounter : public Engine::Rectangle {
public:
  FlagCounter(int x, int y, int w, int h)
      : Rectangle{x, y, w, h, Config::FLAG_COUNTER_COLOR},
        image_{x,
               y,
               Config::FOOTER_HEIGHT - Config::PADDING,
               Config::FOOTER_HEIGHT - Config::PADDING,
               Config::FLAG_IMAGE,
               24},
        text_{x + Config::FOOTER_HEIGHT,
              y,
              w - Config::FOOTER_HEIGHT - 24,
              h,
              std::to_string(Config::BOMB_COUNT),
              {255, 255, 255, 255},
              20} {}

  void render(SDL_Surface *surface) override {
    Rectangle::render(surface);
    image_.render(surface);
    text_.render(surface);
  }

  void handleEvent(const SDL_Event &event) {
    if (event.type == UserEvents::FLAG_PLACED) {
      --flagsAvailable_;
    } else if (event.type == UserEvents::FLAG_CLEARED) {
      ++flagsAvailable_;
    } else if (event.type == UserEvents::NEW_GAME) {
      flagsAvailable_ = Config::BOMB_COUNT;
    } else if (event.type == UserEvents::GAME_WON) {
      flagsAvailable_ = 0;
    } else {
      return;
    }
    text_.setText(std::to_string(flagsAvailable_));
  }

private:
  int flagsAvailable_{Config::BOMB_COUNT};
  Engine::Image image_;
  Engine::Text text_;
};

#endif // !FLAG_COUNTER_H

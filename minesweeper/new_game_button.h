#ifndef NEW_GAME_BUTTON_H
#define NEW_GAME_BUTTON_H

#include "engine/button.h"
#include "engine/text.h"

class NewGameButton : public Engine::Button {
public:
  NewGameButton(int x, int y, int w, int h)
      : Button{x, y, w, h}, text_{x, y, w, h, "New Game", {}, 20} {}

  void render(SDL_Surface *surface) override {
    Button::render(surface);
    text_.render(surface);
  }

  void handleLeftClick() override {
    SDL_Event newGameEvent{UserEvents::NEW_GAME};
    SDL_PushEvent(&newGameEvent);
  }

private:
  Engine::Text text_;
};

#endif // !NEW_GAME_BUTTON_H

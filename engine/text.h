#ifndef TEXT_H
#define TEXT_H

#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace Engine {
class Text {
public:
  Text(int x, int y, int w, int h, const std::string &content,
       SDL_Color color = {0, 0, 0, 255}, int fontSize = 30)
      : destinationRect_{x, y, w, h}, color_{color} {
    font_ = TTF_OpenFont(Config::FONT.c_str(), fontSize);
#ifdef SHOW_DEBUG_INFO
    Utils::checkSDLError("TTF_OpenFont");
#endif
    setText(content);
  }

  void setText(const std::string &text) { setText(text, color_); }

  void setText(const std::string &text, SDL_Color newColor) {
    if (textSurface_) {
      SDL_FreeSurface(textSurface_);
    }
    color_ = newColor;

    textSurface_ = TTF_RenderUTF8_Blended(font_, text.c_str(), color_);

    auto [x, y, w, h] = destinationRect_;

    // horrizontally centering
    const int widthDifference{w - textSurface_->w};
    const int leftOffset{widthDifference / 2};

    // vertically centering
    const int heightDifference{h - textSurface_->h};
    const int topOffset{heightDifference / 2};

    textPosition_ = {x + leftOffset, y + topOffset, w, h};
  }

  void render(SDL_Surface *surface) {
    SDL_BlitSurface(textSurface_, nullptr, surface, &textPosition_);
  }

  ~Text() {
    if (font_)
      TTF_CloseFont(font_);
    if (textSurface_)
      SDL_FreeSurface(textSurface_);
  }

private:
  SDL_Surface *textSurface_{nullptr};
  TTF_Font *font_{nullptr};
  SDL_Rect destinationRect_{0, 0, 0, 0};
  SDL_Rect textPosition_{0, 0, 0, 0};
  SDL_Color color_{0, 0, 0, 255};
};

} // namespace Engine

#endif

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
      : m_destinationRect{x, y, w, h}, m_color{color} {
    m_font = TTF_OpenFont(Config::c_font.c_str(), fontSize);
#ifdef SHOW_DEBUG_INFO
    Utils::checkSDLError("TTF_OpenFont");
#endif
    setText(content);
  }

  void setText(const std::string &text) { setText(text, m_color); }

  void setText(const std::string &text, SDL_Color newColor) {
    if (m_textSurface) {
      SDL_FreeSurface(m_textSurface);
    }
    m_color = newColor;

    m_textSurface = TTF_RenderUTF8_Blended(m_font, text.c_str(), m_color);

    auto [x, y, w, h] = m_destinationRect;

    // horrizontally centering
    const int widthDifference{w - m_textSurface->w};
    const int leftOffset{widthDifference / 2};

    // vertically centering
    const int heightDifference{h - m_textSurface->h};
    const int topOffset{heightDifference / 2};

    m_textPosition = {x + leftOffset, y + topOffset, w, h};
  }

  void render(SDL_Surface *surface) {
    SDL_BlitSurface(m_textSurface, nullptr, surface, &m_textPosition);
  }

  ~Text() {
    if (m_font)
      TTF_CloseFont(m_font);
    if (m_textSurface)
      SDL_FreeSurface(m_textSurface);
  }

private:
  SDL_Surface *m_textSurface{nullptr};
  TTF_Font *m_font{nullptr};
  SDL_Rect m_destinationRect{0, 0, 0, 0};
  SDL_Rect m_textPosition{0, 0, 0, 0};
  SDL_Color m_color{0, 0, 0, 255};
};

} // namespace Engine

#endif

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

namespace Engine {
class Rectangle {
public:
  Rectangle(int x, int y, int w, int h, SDL_Color color = {0, 0, 0, 255})
      : m_rect{x, y, w, h}, m_color{color} {}

  virtual void render(SDL_Surface *surface) {
    SDL_FillRect(surface, &m_rect,
                 SDL_MapRGB(surface->format, m_color.r, m_color.g, m_color.b));
  }

  void setColor(SDL_Color c) { m_color = c; }

  bool isWithinBounds(int x, int y) {
    if (x < m_rect.x)
      return false;
    if (x > m_rect.x + m_rect.w)
      return false;
    if (y < m_rect.y)
      return false;
    if (y > m_rect.y + m_rect.h)
      return false;
    return true;
  }

  SDL_Rect *rect() { return &m_rect; }

  virtual ~Rectangle() = default;

private:
  SDL_Rect m_rect{0, 0, 0, 0};
  SDL_Color m_color{0, 0, 0, 0};
};
} // namespace Engine
#endif

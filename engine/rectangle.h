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
      : rect_{x, y, w, h}, color_{color} {}

  virtual void render(SDL_Surface *surface) {
    SDL_FillRect(surface, &rect_,
                 SDL_MapRGB(surface->format, color_.r, color_.g, color_.b));
  }

  void setColor(SDL_Color c) { color_ = c; }

  bool isWithinBounds(int x, int y) {
    if (x < rect_.x)
      return false;
    if (x > rect_.x + rect_.w)
      return false;
    if (y < rect_.y)
      return false;
    if (y > rect_.y + rect_.h)
      return false;
    return true;
  }

  SDL_Rect *rect() { return &rect_; }

  virtual ~Rectangle() = default;

private:
  SDL_Rect rect_{0, 0, 0, 0};
  SDL_Color color_{0, 0, 0, 0};
};
} // namespace Engine
#endif

#ifndef IMAGE_H
#define IMAGE_H

#include "globals.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <string>

namespace Engine {
class Image {
public:
  Image(int x, int y, int w, int h, const std::string &filename,
        int padding = 12)
      : m_destination{x + padding / 2, y + padding / 2, w - padding,
                      h - padding} {
    m_imageSurface = IMG_Load(filename.c_str());
#ifdef SHOW_DEBUG_INFO
    Utils::checkSDLError("IMG_Load");
#endif
  }

  void render(SDL_Surface *surface) {
    SDL_LowerBlitScaled(m_imageSurface, nullptr, surface, &m_destination);
  }

  ~Image() {
    if (m_imageSurface) {
      SDL_FreeSurface(m_imageSurface);
    }
  }

private:
  SDL_Surface *m_imageSurface{nullptr};
  SDL_Rect m_destination{0, 0, 0, 0};
};
} // namespace Engine

#endif

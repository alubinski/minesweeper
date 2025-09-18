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
      : destination_{x + padding / 2, y + padding / 2, w - padding,
                     h - padding} {
    imageSurface_ = IMG_Load(filename.c_str());
#ifdef SHOW_DEBUG_INFO
    Utils::checkSDLError("IMG_Load");
#endif
  }

  void render(SDL_Surface *surface) {
    SDL_LowerBlitScaled(imageSurface_, nullptr, surface, &destination_);
  }

  ~Image() {
    if (imageSurface_) {
      SDL_FreeSurface(imageSurface_);
    }
  }

private:
  SDL_Surface *imageSurface_{nullptr};
  SDL_Rect destination_{0, 0, 0, 0};
};
} // namespace Engine

#endif

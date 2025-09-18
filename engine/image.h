#ifndef IMAGE_H
#define IMAGE_H

#include "globals.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <string>
#include <unistd.h>

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
    SDL_BlitScaled(imageSurface_, nullptr, surface, &destination_);
  }

  Image(const Image &) = delete;
  Image &operator=(const Image &) = delete;

  Image(Image &&other) noexcept
      : imageSurface_{other.imageSurface_}, destination_{other.destination_} {
    other.imageSurface_ = nullptr;
  }

  Image &operator=(Image &&other) noexcept {
    if (this != &other) {
      if (imageSurface_)
        SDL_FreeSurface(imageSurface_);
      imageSurface_ = other.imageSurface_;
      destination_ = other.destination_;
      other.imageSurface_ = nullptr;
    }
    return *this;
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

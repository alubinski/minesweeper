#ifndef WINDOW_H
#define WINDOW_H

#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

namespace Engine {

class Window {
public:
  Window() {
    SDLWindow_ =
        SDL_CreateWindow(Config::GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, Config::WINDOW_WIDTH,
                         Config::WINDOW_HEIGHT, 0);
  }

  void render() {
    SDL_FillRect(surface(), nullptr,
                 SDL_MapRGB(surface()->format, Config::BACKGROUND_COLOR.r,
                            Config::BACKGROUND_COLOR.g,
                            Config::BACKGROUND_COLOR.b));
  }

  void update() { SDL_UpdateWindowSurface(SDLWindow_); }

  SDL_Surface *surface() { return SDL_GetWindowSurface(SDLWindow_); }

  ~Window() {
    if (SDLWindow_ && SDL_WasInit(SDL_INIT_VIDEO)) {
      SDL_DestroyWindow(SDLWindow_);
    }
  }

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

private:
  SDL_Window *SDLWindow_{nullptr};
};

} // namespace Engine

#endif

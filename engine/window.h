#ifndef WINDOW_H
#define WINDOW_H

#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <fstream>

namespace Engine {

class Window {
public:
  Window() {
    m_SDLWindow =
        SDL_CreateWindow(Config::c_gameName.c_str(), SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, Config::c_windowWidth,
                         Config::c_windowHeight, 0);
  }

  void render() {
    SDL_FillRect(surface(), nullptr,
                 SDL_MapRGB(surface()->format, Config::c_backgroundColor.r,
                            Config::c_backgroundColor.g,
                            Config::c_backgroundColor.b));
  }

  void update() { SDL_UpdateWindowSurface(m_SDLWindow); }

  SDL_Surface *surface() { return SDL_GetWindowSurface(m_SDLWindow); }

  ~Window() {
    if (m_SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
      SDL_DestroyWindow(m_SDLWindow);
    }
  }

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

private:
  SDL_Window *m_SDLWindow{nullptr};
};

} // namespace Engine

#endif

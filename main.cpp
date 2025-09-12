#include "engine/window.h"
#include "globals.h"
#include "minesweeper/ui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_VIDEO);
#ifdef SHOW_DEBUG_INFO
  Utils::checkSDLError("SDL_Init");
#endif

  IMG_Init(IMG_INIT_PNG);
#ifdef SHOW_DEBUG_INFO
  Utils::checkSDLError("IMG_Init");
#endif

  TTF_Init();
#ifdef SHOW_DEBUG_INFO
  Utils::checkSDLError("TTF_Init");
#endif

  Engine::Window gameWindow;
  MinesweeperUI ui;

  SDL_Event event;
  bool shouldQuit{false};

  while (!shouldQuit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        shouldQuit = true;
      } else {
        ui.handleEvent(event);
      }
    }

    gameWindow.render();
    ui.render(gameWindow.surface());

    gameWindow.update();
  }

  SDL_Quit();
  return 0;
}

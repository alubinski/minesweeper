#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL_stdinc.h>
#define SHOW_DEBUG_INFO

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

namespace UserEvents {
inline Uint32 CELL_CLEARED = SDL_RegisterEvents(1);
inline Uint32 BOMB_PLACED = SDL_RegisterEvents(1);
} // namespace UserEvents

namespace Config {
// Game Settings
inline const std::string GAME_NAME{"Minesweeper"};
inline constexpr int GRID_COLUMNS{8};
inline constexpr int GRID_ROWS{4};
inline constexpr int BOMB_COUNT{6};

// Size and Positioning
inline constexpr int PADDING{5};
inline constexpr int CELL_SIZE{50};

inline constexpr int GRID_HEIGHT{GRID_ROWS * CELL_SIZE +
                                 (GRID_ROWS - 1) * PADDING};
inline constexpr int GRID_WIDTH{GRID_COLUMNS * CELL_SIZE +
                                (GRID_COLUMNS - 1) * PADDING};

inline constexpr int WINDOW_HEIGHT{GRID_HEIGHT + 2 * PADDING};
inline constexpr int WINDOW_WIDTH{GRID_WIDTH + 2 * PADDING};

// Colors
inline constexpr SDL_Color BACKGROUND_COLOR{170, 170, 170, 255};
inline constexpr SDL_Color BUTTON_COLOR{200, 200, 200, 255};
inline constexpr SDL_Color BUTTON_HOVER_COLOR{170, 170, 170, 255};
inline constexpr SDL_Color BUTTON_CLEARED_COLOR{240, 240, 240, 255};

// Asset Paths
inline const std::string FONT{"Rubik-SemiBold.ttf"};
inline const std::string BOMB_IMAGE{
    "/home/alubinski/dev/minesweeper/build/bomb.png"};

static_assert(BOMB_COUNT < GRID_COLUMNS * GRID_ROWS,
              "Bomb count must be less than total cells");
} // namespace Config

namespace Utils {
#ifdef SHOW_DEBUG_INFO
inline void checkSDLError(const std::string &msg) {
  const char *error = SDL_GetError();
  if (*error != '\0') {
    std::cerr << msg << " Error: " << error << std::endl;
    SDL_ClearError();
  }
}
#endif
} // namespace Utils

#endif

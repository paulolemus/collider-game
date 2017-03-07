#ifndef COLLIDER_WINDOW_H
#define COLLIDER_WINDOW_H

#include "SDL2/SDL.h"

/// @brief Encapsulates the SDL Window creation.
class Window {
public:
  Window(const char* title, size_t w, size_t h) {
    //Create the window centered at 720p
    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              w,
                              h,
                              SDL_WINDOW_OPENGL);
    if (window == nullptr) {
      std::cerr << "Window creation error.\n";
      throw std::runtime_error(SDL_GetError());
    }
  }

  /// @brief Alternate constructor for custom flags
  Window(const char* title, size_t w, size_t h, Uint32 flags) {
    // Create the window centered at 720p
    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              w,
                              h,
                              flags);
    if (window == nullptr) {
      std::cerr << "Window creation error.\n";
      throw std::runtime_error(SDL_GetError());
    }
  }

  /// @brief Destructor needs to release the resources
  ///        through SDL
  ~Window() {
    SDL_DestroyWindow(window);
  }

  /// @brief Just returns the pointer to the window.
  SDL_Window* get() {
    return window;
  }

private:
  SDL_Window* window;
};

#endif // COLLIDER_WINDOW_H

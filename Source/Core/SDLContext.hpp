#pragma once

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <stdexcept>
class SDLContext {
public:
  SDLContext() {
    // 1. Icializa SDL3
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
      throw std::runtime_error(SDL_GetError());
    }
    // 2.SDL_image no es necesario inicializarlor
    if (!TTF_Init())
      throw std::runtime_error("Error al cargar SDl_ttf");
  };
  ~SDLContext() {
    // WARNING: HAy que hacerlo en orden SDL_INIT_VIDEO
    TTF_Quit();
    SDL_Quit();
  };
  SDLContext(const SDLContext &) = delete;
  SDLContext &operator=(const SDLContext &) = delete;
};

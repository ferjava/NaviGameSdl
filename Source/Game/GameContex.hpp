#pragma once
#include "../Core/TextureManager.hpp"
#include "SDL3/SDL_rect.h"
// Estructura para pasar parametros como anchura altura Estructura
struct GameContext {
  SDL_FRect pantalla;
  TextureManager *tm;
};

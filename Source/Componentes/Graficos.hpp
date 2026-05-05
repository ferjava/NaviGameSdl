#pragma once
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <memory>

namespace GC {
/// @brief: Determina la asociacion de una SDL_Textura y el recorte de esta

struct Sprite {
  std::shared_ptr<SDL_Texture> sprite;
  SDL_FRect source;
};

} // namespace GC

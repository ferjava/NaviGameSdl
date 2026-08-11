#pragma once
#include "../Core/SceneManager.hpp"
#include "../Core/TextureManager.hpp"
#include "SDL3/SDL_rect.h"
#include "entt/entity/fwd.hpp"
#include <vector>
// Estructura para pasar parametros como anchura altura Estructura
struct GameContext {
  SDL_FRect pantalla;
  TextureManager *tm;
  SDL_Renderer *render;
  float *delta_time;
  std::vector<entt::entity> elimina_entidad;
  SceneManager *director;
};

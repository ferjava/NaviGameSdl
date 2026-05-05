#pragma once

#include "SDL3/SDL_render.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
namespace Sistema {
void Movimiento(entt::registry &reg, float dt); // Declaracion para movimiento
void Dibujado(entt::registry &reg,
              SDL_Renderer *render); // Declaracion del sistema Dibujado

} // namespace Sistema

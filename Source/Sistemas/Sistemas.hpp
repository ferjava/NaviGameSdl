#pragma once

#include "SDL3/SDL_render.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"

namespace Sistema {
void Movimiento(entt::registry &reg, float dt); // Declaracion para movimiento
void Dibujado(entt::registry &reg,
              SDL_Renderer *render); // Declaracion del sistema Dibujado
void Entrada_Teclado(entt::registry &reg,
                     float dt); // Declaracion de la asignacion de
                                // teclas al movimiento
void Frontera(entt::registry &reg,
              SDL_FRect &area); // Limita el movimiento fuera de la pantalla

void Colisones(entt::registry &reg);
void Animaciones(entt::registry &reg, float dt);
namespace IA {
void GeneraBalas(entt::registry &reg, float dt);

}

} // namespace Sistema

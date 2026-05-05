#include "../Componentes/transformadas.hpp"
#include "Sistemas.hpp"
void Sistema::Movimiento(entt::registry &reg, float dt) {
  auto view = reg.view<GC::Posicion, GC::Velocidad>();
  for (auto entity : view) {
    auto &pos = view.get<GC::Posicion>(entity);
    auto &vel = view.get<GC::Velocidad>(entity);

    pos.X += vel.Vx * dt;
    pos.Y += vel.Vy * dt;
  }
}

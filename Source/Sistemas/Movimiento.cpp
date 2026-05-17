#include "../Componentes/Componentes.hpp"
#include "SDL3/SDL_log.h"
#include "Sistemas.hpp"
#include "entt/entity/fwd.hpp"
void Sistema::Movimiento(entt::registry &reg, float dt) {
  auto view = reg.view<GC::Posicion, GC::Velocidad>();
  std::vector<entt::entity> EntidadParaDestruir;
  for (auto enti : view) {
    auto &pos = view.get<GC::Posicion>(enti);
    auto &vel = view.get<GC::Velocidad>(enti);

    pos.X += vel.Vx * dt;
    pos.Y += vel.Vy * dt;
    // Comprobamos las balas
    if (reg.all_of<GC::Bala>(enti)) {
      if (pos.Y <= 0) {
        EntidadParaDestruir.push_back(enti);
      }
    }
  }
  for (auto entidad : EntidadParaDestruir) {
    reg.destroy(entidad);
    SDL_Log("Bala destruida ");
  }
}

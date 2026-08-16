#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/GameConfig.hpp"
#include "SDL3/SDL_log.h"
#include "Sistemas.hpp"
#include <strings.h>
void Sistema::IA::MoviAutomatico(entt::registry &reg, float dt,
                                 GameContext ctx) {
  auto view = reg.view<GC::Posicion, GC::Velocidad, ::IA::Moviment>();
  {
    for (auto enti : view) {
      auto &pos = reg.get<GC::Posicion>(enti);  // Cojemos la posicion actual
      auto &vel = reg.get<GC::Velocidad>(enti); // cojemos la direccion que
                                                // lleva
      // pos.X += vel.Vx * dt;
      // pos.Y += vel.Vy * dt;
      auto &dest = reg.get<::IA::Moviment>(enti); // punto de destino ;
      bool ha_llegado = Utils::Move_To(pos, dest.destino[dest.indice], vel, dt);

      if (ha_llegado) {
        if (dest.indice == dest.destino.size() - 1) {
          // reinciamos
          pos = dest.destino[dest.indice];
          dest.indice = 0;
        } else {
          pos = dest.destino[dest.indice];
          dest.indice = dest.indice + 1;

          // Incremeta en el vector
        }
      }
      if (reg.all_of<GC::Raptor>(enti)) {
        // Acciones::moveRaptor(reg, dt);
      }
    }
  }
}

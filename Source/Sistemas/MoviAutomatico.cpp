#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/GameConfig.hpp"
#include "SDL3/SDL_log.h"
#include "Sistemas.hpp"
#include <strings.h>
void Sistema::IA::MoviAutomatico(entt::registry &reg, float dt,
                                 GameContext ctx) {
  // Limpiamos todos los PosChange para añadir los nuevos
  reg.clear<::IA::PosChange>();

  auto view = reg.view<GC::Posicion, GC::Velocidad, ::IA::Moviment>();
  {
    for (auto enti : view) {
      auto &pos = reg.get<GC::Posicion>(enti);  // Cojemos la posicion actual
      auto &vel = reg.get<GC::Velocidad>(enti); // cojemos la direccion que
                                                // lleva
      bool ha_llegado = false;
      auto &dest = reg.get<::IA::Moviment>(enti); // punto de destino ;
      if (!dest.destino.empty()) {

        ha_llegado = Utils::Move_To(pos, dest.destino[dest.indice], vel, dt);
      } else {
        ha_llegado = false;
      }
      if (ha_llegado) {
        reg.emplace_or_replace<::IA::PosChange>(enti);

        if (dest.indice == dest.destino.size() - 1) {
          reg.emplace_or_replace<::IA::MoveEnd>(enti);
          //  reinciamos
          if (dest.repeat) {
            pos = dest.destino[dest.indice];

            dest.indice = 0;
          } else {
            // reg.emplace_or_replace<::IA::MoveEnd>(enti);

            // continue;
          }
        } else {
          pos = dest.destino[dest.indice];
          dest.indice = dest.indice + 1;

          // Incremeta en el vector}
        }
      }
      if (reg.all_of<GC::Boss>(enti)) {

        Acciones::moveBoss(reg, ctx);
      }
    }
  }
}

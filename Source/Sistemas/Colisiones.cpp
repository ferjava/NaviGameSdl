#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/NaviGame.hpp"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "Sistemas.hpp"
#include <asm-generic/errno.h>
#include <functional>
#include <memory>
// NOTE: Para que funcione bien se debe actualizar despues del Sistema de
// Movimiento
//
void Sistema::Colisones(entt::registry &reg) {
  // Crea un vector para classmpiar
  std::vector<entt::entity> EntidadParaDestruir;
  // Limpiar el estado de las Colisones
  auto view = reg.view<GC::Collidable>();
  for (auto entidad : view) {
    reg.get<GC::Collidable>(entidad).isColliding = false;
  }
  // Obtener los que pueden colisionar
  auto ColisionView = reg.view<GC::Collidable, GC::Sprite>();
  for (auto entiA : ColisionView) {
    auto &colA = ColisionView.get<GC::Collidable>(entiA);
    auto &spA = ColisionView.get<GC::Sprite>(entiA);
    if (spA.dest.x <= 0.0f | spA.dest.y <= 0.0f)
      continue;
    colA.BoxCollidable = spA.dest;

    for (auto entiB : ColisionView) {
      auto &colB = ColisionView.get<GC::Collidable>(entiB);
      auto &spB = ColisionView.get<GC::Sprite>(entiB);
      if (spB.dest.x <= 0.0f | spB.dest.y <= 0.0f)
        continue;
      colB.BoxCollidable = spB.dest;

      if (entiA == entiB)
        continue; // No podemos chocar contra nsosotros

      if (SDL_HasRectIntersectionFloat(&colA.BoxCollidable,
                                       &colB.BoxCollidable)) {
        // No chocamos con nuestras balas
        if (reg.all_of<GC::BalaPlayer>(entiA) &&
            reg.all_of<GC::Player>(entiB)) {
          continue;
        } else if (reg.all_of<GC::Player>(entiA) &&
                   reg.all_of<GC::BalaPlayer>(entiB)) {
          continue;
        }
        if (reg.all_of<GC::Enemy>(entiA) && reg.all_of<GC::Enemy>(entiB)) {
          continue;
        }

        colA.isColliding = true;
        colB.isColliding = true;
      }
      if (colA.isColliding && colB.isColliding) {
        SDL_Log("Colison efectuada");

        colA.alcolisonar(reg, entiA, EntidadParaDestruir, NaviGame::ctx);
        colB.alcolisonar(reg, entiB, EntidadParaDestruir, NaviGame::ctx);
      }

      // Nuestra logica de colision
    }
  }
  for (auto entidad : EntidadParaDestruir) {
    if (reg.valid(entidad)) {

      reg.destroy(entidad);
    }
  }
}

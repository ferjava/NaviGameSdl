#include "../Componentes/GameTags.hpp"
#include "../Componentes/Graficos.hpp"
#include "../Componentes/transformadas.hpp"
#include "Sistemas.hpp"
///
///@brief:: Compruab y limita al Player  que no se salga de la pantalla
///@param : reg es el registro de entt de la escena
///@param area Es el rectangulo de la pantalla
void Sistema::Frontera(entt::registry &reg, SDL_FRect &area) {
  auto view = reg.view<GC::Player, GC::Posicion, GC::Sprite>();
  for (auto entidad : view) {
    auto &pos = view.get<GC::Posicion>(entidad);
    auto &spr = view.get<GC::Sprite>(entidad);

    if (pos.X < area.x) {
      pos.X = area.x;
    }
    if ((pos.X + spr.source.w / 2) > area.w) {
      pos.X = area.w - spr.source.w / 2;
    }
    if (pos.Y < area.y) {
      pos.Y = area.y;
    }
    if ((pos.Y + spr.source.h / 2) > area.h) {
      pos.Y = area.h - spr.source.h / 2;
    }
  }
}

#include "../Componentes/Componentes.hpp"
#include "Sistemas.hpp"
void Sistema::Animaciones(entt::registry &reg, float dt) {
  float animatimer = 0.0f;
  auto view = reg.view<GC::Sprite, GC::Animacion>();

  for (auto enti : view) {
    auto &sprite = view.get<GC::Sprite>(enti);
    auto &anima = view.get<GC::Animacion>(enti);
    // Modificamos con el tiempo
    animatimer += dt;

    for (auto actualframe = anima.frame.begin();
         actualframe != anima.frame.end();) {
      sprite.source = *actualframe;
      if (animatimer >= anima.time) {
        animatimer = 0.0f;
        actualframe++;
      }
      if (actualframe == anima.frame.end()) {
        anima.terminada = true;
      }

      if (actualframe == anima.frame.end() && anima.repite) {
        actualframe = anima.frame.begin();
      }
    }
    anima.terminada = true;
  }
}

#include "../Componentes/Componentes.hpp"
#include "Sistemas.hpp"

int indice = 0;
float animatimer = 0.0f;
void Sistema::Animaciones(entt::registry &reg, float dt) {
  // float animatimer = 0.0f;
  auto view = reg.view<GC::Sprite, GC::Animacion>();
  animatimer += dt;
  for (auto enti : view) {
    auto &sprite = view.get<GC::Sprite>(enti);
    auto &anima = view.get<GC::Animacion>(enti);
    // Modificamos con el tiempo

    if (indice < anima.frame.size()) {
      auto actualframe = anima.frame[indice];
      sprite.source = actualframe;
      if (animatimer > anima.time) {
        animatimer = 0.0f;
        indice++;
        if (indice >= anima.frame.size()) {
          indice = anima.frame.size();
        }
      }
    } else {

      if (anima.repite) {
        // sprite.source = actualframe;
        indice = 0;
      } else {
        reg.destroy(enti);
      }
      // if (indice == anima.frame.size()) {
      // sprite.source = actualframe;

      anima.terminada = true;
    }
  }
}

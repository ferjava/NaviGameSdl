#include "../Componentes/Componentes.hpp"
#include "Sistemas.hpp"
#include "entt/entity/fwd.hpp"

int indice = 0;
float animatimer = 0.0f;
void Sistema::Animaciones(entt::registry &reg, float dt) {
  std::vector<entt::entity> destoy_animacion;
  // float animatimer = 0.0f;
  auto view = reg.view<GC::Sprite, GC::Animacion>();
  animatimer += dt;
  for (auto enti : view) {
    auto &sprite = view.get<GC::Sprite>(enti);
    auto &anima = view.get<GC::Animacion>(enti);
    // Modificamos con el tiempo

    if (anima.terminada) {
      indice = 0;
      destoy_animacion.push_back(enti);

      continue;
    } else {
      if (indice < anima.frame.size()) {
        auto actualframe = anima.frame[indice];
        sprite.source = actualframe;
        if (animatimer > anima.time) {
          animatimer = 0.0f;
          indice++;
          if (indice >= anima.frame.size()) {
            indice = anima.frame.size();
            anima.terminada = true;
          }
        }
      } else {

        if (anima.repite) {
          // sprite.source = actualframe;

          indice = 0;
          anima.terminada = false;
        }
        anima.terminada = true;
      }
    }
  }

  for (auto enit : destoy_animacion) {
    reg.destroy(enit);
  }
}

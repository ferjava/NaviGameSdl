#include "../Componentes/Graficos.hpp"
#include "../Componentes/transformadas.hpp"
#include "SDL3/SDL_render.h"
#include "Sistemas.hpp"
void Sistema::Dibujado(entt::registry &reg, SDL_Renderer *render) {
  auto view = reg.view<GC::Posicion, GC::Sprite>();
  for (auto entity : view) {
    float des_width = 50.0f;
    float des_Heigh = 50.0f;
    auto &pos = view.get<GC::Posicion>(entity);
    auto &spr = view.get<GC::Sprite>(entity);
    SDL_FRect dest{pos.X, pos.Y, des_width, des_Heigh};
    SDL_RenderTexture(render, spr.sprite.get(), &spr.source, &dest);
  }
}

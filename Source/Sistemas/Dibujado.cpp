#include "../Componentes/Graficos.hpp"
#include "../Componentes/transformadas.hpp"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sistemas.hpp"
void Sistema::Dibujado(entt::registry &reg, SDL_Renderer *render) {
  auto view = reg.view<GC::Posicion, GC::Sprite>();
  for (auto entity : view) {
    auto &pos = view.get<GC::Posicion>(entity);
    auto &spr = view.get<GC::Sprite>(entity);
    SDL_FRect dest{pos.X, pos.Y, spr.source.w, spr.source.h};
    if (SDL_RectEmptyFloat(&spr.dest)) {
      spr.dest = dest;
    } else {
      spr.dest.x = pos.X;
      spr.dest.y = pos.Y;
    }

    SDL_RenderTexture(render, spr.sprite.get(), &spr.source, &spr.dest);
  }
}

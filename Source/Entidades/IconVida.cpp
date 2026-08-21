#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/GameConfig.hpp"
#include "SDL3/SDL_rect.h"
void Factory::createIconVida(entt::registry &reg, GameContext &ctx) {

  auto icon_sprite = ctx.tm->getTexture("assets/images/naveicono.png");
  SDL_FRect spr_orig(0, 0, icon_sprite->w, icon_sprite->h);
  SDL_FRect spr_dest(0, 0, icon_sprite->w * 2, icon_sprite->h * 2);
  for (int i = 0; i < Game::Player::LIVES - 1; i++) {
    auto icon_nave = reg.create();
    reg.emplace<GC::Posicion>(
        icon_nave, 0.0f + (icon_sprite->w * 2) * i,
        ctx.pantalla.h - icon_sprite->h * 2); // Colocamos fuera de la pantalla
    reg.emplace<GC::IconPlayer>(icon_nave);
    reg.emplace<GC::Sprite>(icon_nave, icon_sprite, spr_orig, spr_dest);
  }
}

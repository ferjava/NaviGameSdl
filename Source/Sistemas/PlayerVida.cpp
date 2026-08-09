#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/GameConfig.hpp"
#include "../Game/GameContex.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"
float livestart = 0.0f;
void Sistema::IA::PlayerVida(entt::registry &reg, float dt, GameContext ctx) {
  auto view = reg.view<GC::Posicion, GC::Velocidad, GC::Player, ::IA::Live,
                       GC::Collidable, GC::Sprite>();
  for (auto enti : view) {
    auto &live = view.get<::IA::Live>(enti);
    auto &vel = view.get<GC::Velocidad>(enti);
    auto &pos = view.get<GC::Posicion>(enti);
    auto &choque = view.get<GC::Collidable>(enti);
    auto &sp = view.get<GC::Sprite>(enti);
    if (!live.is_live) {
      livestart += dt;
      if (livestart >= 2.0f) {
        SDL_SetTextureAlphaMod(sp.sprite.get(), 255);
        choque.isCollidable = true;
        live.is_live = true;
        livestart = 0.0f;
        vel.Vx = Game::Player::SPEED;
        vel.Vy = Game::Player::SPEED;
      } else {
        Efecto::Blink(sp.sprite.get(), 0.2f, ctx);
        choque.isCollidable = false;
        vel.Vx = 0.0f;
        vel.Vy = -200.0f;
      }
    }
  }
}

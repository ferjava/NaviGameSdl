#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/GameConfig.hpp"
#include "../Game/NaviGame.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_scancode.h"
#include "Sistemas.hpp"
#include "entt/entity/fwd.hpp"
float disparoTimer = 0.0f;
const float COOLDOWN_DISPARO = 0.2f;

void Sistema::Entrada_Teclado(entt::registry &reg, float dt) {
  auto view = reg.view<GC::Player, GC::Velocidad, GC::Posicion, GC::Sprite,
                       ::IA::Live>();
  const bool *keys = SDL_GetKeyboardState(nullptr);
  disparoTimer += dt;

  for (auto entity : view) {
    auto &vel = view.get<GC::Velocidad>(entity);
    auto &sp = view.get<GC::Sprite>(entity);
    auto &live = view.get<::IA::Live>(entity);
    // Comprobamos que este vivo

    vel.Vx = 0.0f;
    vel.Vy = 0.0f;
    if (!live.is_live)
      continue;
    sp.source.x = Game::Player::ANIMACION[4];
    if (keys[SDL_SCANCODE_UP]) {
      vel.Vy = -Game::Player::SPEED;
    }
    if (keys[SDL_SCANCODE_DOWN])
      vel.Vy = Game::Player::SPEED;
    if (keys[SDL_SCANCODE_RIGHT]) {
      sp.source.x = Game::Player::ANIMACION[6];
      vel.Vx = Game::Player::SPEED;
    }

    if (keys[SDL_SCANCODE_LEFT]) {
      sp.source.x = Game::Player::ANIMACION[0];
      vel.Vx = -Game::Player::SPEED;
    }
    if (keys[SDL_SCANCODE_SPACE]) {
      if (disparoTimer >= COOLDOWN_DISPARO) {
        disparoTimer = 0.0f;
        auto _bala1 = Factory::creatBulletPlayer(reg, NaviGame::ctx);
        auto &bpos = view.get<GC::Posicion>(_bala1);
        bpos = view.get<GC::Posicion>(entity);
        bpos.X = bpos.X + 15.0f;
        bpos.Y = bpos.Y + 25.0f;

        auto _bala2 = Factory::creatBulletPlayer(reg, NaviGame::ctx);
        auto &bpos2 = view.get<GC::Posicion>(_bala2);
        bpos2 = view.get<GC::Posicion>(entity);
        bpos2.X = bpos2.X + 50.0f;
        bpos2.Y = bpos2.Y + 25.0f;
      }
    }
  }
};

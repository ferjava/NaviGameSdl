#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/NaviGame.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_scancode.h"
#include "Sistemas.hpp"
float disparoTimer = 0.0f;
const float COOLDOWN_DISPARO = 0.2f;
std::vector<float> ANIMACION = {0, 100, 200, 300, 400, 500, 600};

void Sistema::Entrada_Teclado(entt::registry &reg, float dt) {
  auto view = reg.view<GC::Player, GC::Velocidad, GC::Posicion, GC::Sprite>();
  const bool *keys = SDL_GetKeyboardState(nullptr);
  disparoTimer += dt;
  for (auto entity : view) {
    auto &vel = view.get<GC::Velocidad>(entity);
    auto &sp = view.get<GC::Sprite>(entity);
    float speed = 200.0f;
    vel.Vx = 0.0f;
    vel.Vy = 0.0f;
    sp.source.x = ANIMACION[4];
    if (keys[SDL_SCANCODE_UP]) {
      vel.Vy = -speed;
    }
    if (keys[SDL_SCANCODE_DOWN])
      vel.Vy = speed;
    if (keys[SDL_SCANCODE_RIGHT]) {
      sp.source.x = ANIMACION[6];
      vel.Vx = speed;
    }

    if (keys[SDL_SCANCODE_LEFT]) {
      sp.source.x = ANIMACION[0];
      vel.Vx = -speed;
    }
    if (keys[SDL_SCANCODE_SPACE]) {
      if (disparoTimer >= COOLDOWN_DISPARO) {
        disparoTimer = 0.0f;
        auto _bala1 = Factory::creatBullet(reg, NaviGame::ctx);
        auto &bpos = view.get<GC::Posicion>(_bala1);
        bpos = view.get<GC::Posicion>(entity);
        bpos.X = bpos.X + 7.5f;
        auto _bala2 = Factory::creatBullet(reg, NaviGame::ctx);
        auto &bpos2 = view.get<GC::Posicion>(_bala2);
        bpos2 = view.get<GC::Posicion>(entity);
        bpos2.X = bpos2.X + 25.0f;
      }
    }
  }
};

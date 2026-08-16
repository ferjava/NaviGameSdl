#include "../Componentes/Componentes.hpp"
#include "../Game/GameConfig.hpp"
#include "Entidades.hpp"
#include "SDL3/SDL_log.h"
#include "Utils/Utils.hpp"
#include "entt/entity/fwd.hpp"

void colisionRaptor(entt::registry &reg, entt::entity &entidad,
                    std::vector<entt::entity> &destroyer, GameContext &ctx) {
  // 1.Comprobar que esta vivo
  auto &living = reg.get<IA::Live>(entidad);

  if (living.is_live) // esta vivo
  {
    if (living.Heal > 0) // tiene heal
    {
      --living.Heal; // Pierde vida
    } else           // no tiene heal
    {
      --living.lives;         // Quitamos la vida
      living.is_live = false; // Esta muerto
    }
    // Tiene alguna vida ?
    if (living.lives == 0) {
      living.is_live = false;

    } else // Si tiene alguna vida resucita
    {
      living.is_live = true;
    }
  } else // esta muerto
  {
    // creamos la explosion
    auto explosion = Factory::createExplosion(reg, ctx);
    auto &explo_pos = reg.get<GC::Posicion>(explosion);
    auto &enti_pos = reg.get<GC::Posicion>(entidad);
    explo_pos = enti_pos; // Colocamos la esplosion en lugar de la nave
    ctx.elimina_entidad.push_back(entidad);
  }
}
void variasbalas(entt::entity &entidad, entt::registry &reg, GameContext &ctx) {
  // TODO: Dispara varias balas en distintas direcciones
}
bool lado = true;
entt::entity Factory::createEnemyRaptor(entt::registry &reg, GameContext &ctx) {
  using namespace Game::Enemy::Raptor;

  auto raptor_sp = ctx.tm->getTexture("assets/images/raptor.png");
  SDL_FRect rect_dest{0.0f, 0.0f, TEXTURE_W, TEXTURE_H};
  SDL_FRect rect_orig{SPRITE_POS_X, SPRITE_POS_Y, TEXTURE_W, TEXTURE_H};
  std::vector<GC::Posicion> destinos;
  SDL_FRect area_izq{1.0f, 1.0f,
                     ctx.pantalla.w / 2 - Game::Enemy::Raptor::TEXTURE_W,
                     ctx.pantalla.h / 2}; // area de movimient
  SDL_FRect area_der{ctx.pantalla.w / 2 + Game::Enemy::Raptor::TEXTURE_W, 1.0f,
                     ctx.pantalla.w - Game::Enemy::Raptor::TEXTURE_W,
                     ctx.pantalla.h / 2 - Game::Enemy::Raptor::TEXTURE_H};

  SDL_FRect area;

  GC::Posicion izqui{0.0f, ctx.pantalla.h / 3};
  GC::Posicion dere{ctx.pantalla.w + Game::Enemy::Raptor::TEXTURE_W,
                    ctx.pantalla.h / 3};
  GC::Posicion swap;

  if (lado) {
    // lado izquiedo
    area = area_izq;
    swap = izqui;
    lado = false;
  } else {
    area = area_der;
    swap = dere;
    lado = true;
  }

  for (int i = 0; i <= 3; i++) {
    int x = Utils::Dado(area.x, area.w);
    int y = Utils::Dado(area.y, area.h);

    SDL_Log("posicion raptor %d en x %d en y %d", i, x, y);
    destinos.push_back(GC::Posicion((float)x, (float)y));
  }
  auto raptor = reg.create();
  reg.emplace<GC::Raptor>(raptor);
  reg.emplace<GC::Posicion>(raptor, swap.X, swap.Y); // Fuera pantalla
  // reg.emplace<GC::Velocidad>(raptor, Game::VELO.Vx, Game::VELO.Vy);
  reg.emplace<GC::Velocidad>(raptor, 0.01f, 0.01f);
  reg.emplace<GC::Sprite>(raptor, raptor_sp, rect_orig, rect_dest);
  reg.emplace<GC::Enemy>(raptor);
  reg.emplace<GC::Collidable>(raptor, false, rect_dest, colisionRaptor, true);
  reg.emplace<IA::Dispara>(raptor, TIME_TO_SHOOT, CARA_DADO_DISPARA,
                           variasbalas);
  reg.emplace<IA::Live>(raptor, 1, HEAL_MAX, true);
  reg.emplace<IA::Moviment>(raptor, destinos, 0);

  return raptor;
}

float disp_timer = 0.0;
void Acciones::moveRaptor(entt::registry &reg, GameContext &ctx) {

  disp_timer += *ctx.delta_time;

  auto view =
      reg.view<GC::Posicion, GC::Velocidad, ::IA::Moviment, GC::Raptor>();
  for (auto enty : view) {
    auto &pos = reg.get<GC::Posicion>(enty);
    auto &movi = reg.get<::IA::Moviment>(enty);
    auto &vel = reg.get<GC::Velocidad>(enty);
    if (disp_timer >= 5.0f) {
      movi.destino.back().Y = 0.0f - Game::Enemy::Raptor::TEXTURE_H * 2;
      vel.Vx = -vel.Vx;
      vel.Vy = -vel.Vy; // sale por arriba
    }
  }
}

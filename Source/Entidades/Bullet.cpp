#include "../Componentes/Componentes.hpp"
#include "../Game/GameConfig.hpp"
#include "Entidades.hpp"
#include "SDL3/SDL_log.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"

void colosion_bala(entt::registry &reg, entt::entity &entidad,
                   std::vector<entt::entity> &destroyer, GameContext &ctx) {

  destroyer.push_back(entidad);
}

entt::entity Factory::creatBulletPlayer(entt::registry &reg, GameContext &ctx) {

  auto _balasp = ctx.tm->getTexture("assets/images/bala.png");
  if (!_balasp)
    SDL_Log("Error al cargar la imagen de bala ");
  SDL_FRect src{0, 0, 32.0f, 32.0f};
  SDL_FRect dest{0, 0, Game::Bala::TAMANO_BALA, Game::Bala::TAMANO_BALA};
  auto bala = reg.create();
  reg.emplace<GC::Sprite>(bala, _balasp, src, dest);
  reg.emplace<GC::Posicion>(bala, 0.0f, 0.0f);
  reg.emplace<GC::Velocidad>(bala, 0.0f, -Game::Bala::VELOCIDAD_BALA);
  reg.emplace<GC::Collidable>(bala, false, dest, colosion_bala);
  reg.emplace<GC::BalaPlayer>(bala);

  return bala;
}

entt::entity Factory::createBullet(entt::registry &reg, GameContext &ctx,
                                   GC::Velocidad direc) {
  auto _balasp = ctx.tm->getTexture("assets/images/bala.png");
  if (!_balasp)
    SDL_Log("Error al cargar la imagen de bala ");
  SDL_FRect src{0, 0, 32.0f, 32.0f};
  SDL_FRect dest{0, 0, Game::Bala::TAMANO_BALA, Game::Bala::TAMANO_BALA};
  auto bala = reg.create();
  reg.emplace<GC::Sprite>(bala, _balasp, src, dest);
  reg.emplace<GC::Posicion>(bala, 0.0f, 0.0f);
  reg.emplace<GC::Velocidad>(bala, direc.Vx, direc.Vy);
  reg.emplace<GC::Collidable>(bala, false, dest, colosion_bala);
  reg.emplace<GC::BalaEnemy>(bala);

  return bala;
}

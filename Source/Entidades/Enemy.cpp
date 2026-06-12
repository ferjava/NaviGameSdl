#include "../Componentes/Componentes.hpp"
#include "../Game/GameConfig.hpp"
#include "Entidades.hpp"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include <memory>

void colisionEnemy(entt::registry &reg, entt::entity &entidad,
                   std::vector<entt::entity> &destroyer, GameContext &ctx) {
  SDL_Log(" Colsion en Enemigo");
  auto exploent = Factory::createExplosion(reg, ctx);
  auto &pos = reg.get<GC::Posicion>(exploent);
  pos = reg.get<GC::Posicion>(entidad);

  destroyer.push_back(entidad);
}
void unabala(entt::entity &entidad, entt::registry &reg, GameContext &ctx) {
  auto bala = Factory::creatBulletEnemy(reg, ctx);
  auto &pos = reg.get<GC::Posicion>(bala);
  pos = reg.get<GC::Posicion>(entidad);
  pos.X = pos.X + Game::Enemy::TEXTURE_W / 2;
  pos.Y = pos.Y + Game::Enemy::TEXTURE_H / 2;
}
entt::entity Factory::createEnemy(entt::registry &reg, GameContext &ctx) {
  // Cargamos el archivo de la imagen del enemigo
  auto sprite = ctx.tm->getTexture("assets/images/enemigos.png");
  SDL_FRect origen{Game::Enemy::MOVE_RIGHT, Game::Enemy::TEXTURE_H * 2.0f,
                   Game::Enemy::TEXTURE_W, Game::Enemy::TEXTURE_H};
  SDL_FRect desti{0.0f, 0.0f, origen.w * 2, origen.h * 2};

  auto nave_enemiga = reg.create();

  reg.emplace<GC::Posicion>(nave_enemiga, 0.0f, ctx.pantalla.h / 6);
  reg.emplace<GC::Velocidad>(nave_enemiga, Game::Enemy::VELOCIDAD_X, 0.0f);
  reg.emplace<GC::Sprite>(nave_enemiga, sprite, origen, desti);
  reg.emplace<GC::Collidable>(nave_enemiga, false, desti, colisionEnemy);
  reg.emplace<GC::Enemy>(nave_enemiga);
  return nave_enemiga;
}
///
/// @brief Crea un grupo de enemigos de l tipo straigth
///
void Factory::createGroupEnemysStraight(entt::registry &reg, GameContext &ctx) {
  auto sprite = ctx.tm->getTexture("assets/images/enemigos.png");

  SDL_FRect origen{Game::Enemy::MOVE_RIGHT, Game::Enemy::TEXTURE_H * 2.0f,
                   Game::Enemy::TEXTURE_W, Game::Enemy::TEXTURE_H};
  SDL_FRect desti{0.0f, 0.0f, origen.w * 2, origen.h * 2};
  for (int i = 0; i < Game::Enemy::Straight::Grupo; i++) {
    auto nave_enemiga = reg.create();
    reg.emplace<GC::Posicion>(
        nave_enemiga,
        -(Game::Enemy::TEXTURE_W + Game::Enemy::TEXTURE_W * 2) * i,
        ctx.pantalla.h / 6);
    reg.emplace<GC::Velocidad>(nave_enemiga, Game::Enemy::VELOCIDAD_X, 0.0f);
    reg.emplace<GC::Sprite>(nave_enemiga, sprite, origen, desti);
    reg.emplace<GC::Collidable>(nave_enemiga, false, desti, colisionEnemy);
    reg.emplace<IA::Dispara>(nave_enemiga, Game::Enemy::Straight::TIME_TO_SHOOT,
                             Game::Enemy::Straight::VALOR_MAX_DISPARO, unabala);
    reg.emplace<GC::Enemy>(nave_enemiga);
  }
}

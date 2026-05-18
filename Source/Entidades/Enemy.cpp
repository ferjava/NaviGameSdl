#include "../Componentes/Componentes.hpp"
#include "../Game/GameConfig.hpp"
#include "Entidades.hpp"
#include "SDL3/SDL_rect.h"
#include "entt/entt.hpp"
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
  reg.emplace<GC::Enemy>(nave_enemiga);
  return nave_enemiga;
}

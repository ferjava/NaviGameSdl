#include "../Componentes/Componentes.hpp"
#include "../Game/GameConfig.hpp"
#include "Entidades.hpp"
#include "SDL3/SDL_rect.h"
#include "entt/entt.hpp"
#include <vector>
entt::entity Factory::createExplosion(entt::registry &reg, GameContext &ctx) {
  auto sprite = ctx.tm->getTexture("assets/images/explosiones.png");
  std::vector<SDL_FRect> animacion;
  SDL_FRect rect;
  for (auto rectx : Game::Explosion::SOURCE_X) {

    rect.h = Game::Explosion::TEXTURE_H;
    rect.w = Game::Explosion::TEXTURE_W;
    rect.y = Game::Explosion::SOURCE_Y;
    rect.x = rectx;
    animacion.push_back(rect);
  }
  auto sprite_src = animacion[0];
  SDL_FRect sprite_dest{0, 0, Game::Enemy::TEXTURE_W * 2,
                        Game::Enemy::TEXTURE_H * 2};
  // Creacion de la entidad en el registro
  auto explosion = reg.create();
  reg.emplace<GC::Posicion>(explosion, -1.0f, -1.0f);
  reg.emplace<GC::Sprite>(explosion, sprite, sprite_src, sprite_dest);
  reg.emplace<GC::Animacion>(explosion, animacion, 0.05f);
  return explosion;
}

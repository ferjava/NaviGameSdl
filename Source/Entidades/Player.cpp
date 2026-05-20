#include "../Componentes/GameTags.hpp"
#include "../Componentes/Graficos.hpp"
#include "../Componentes/transformadas.hpp"
#include "../Game/GameConfig.hpp"
#include "Entidades.hpp"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
entt::entity Factory::createPlayer(entt::registry &reg, GameContext &ctx) {
  auto sprite = ctx.tm->getTexture("assets/images/Naveplayer1.png");
  SDL_FRect sprite_src{300.0f, 0.0f, Game::Player::TEXTURE_W,
                       Game::Player::TEXTURE_W};
  SDL_FRect sprite_dest{0.0f, 0.0f, sprite_src.w, sprite_src.h};
  auto nave = reg.create();

  reg.emplace<GC::Posicion>(nave, ctx.pantalla.w / 2, ctx.pantalla.h / 2);
  reg.emplace<GC::Velocidad>(nave, 0.0f, 0.0f);
  reg.emplace<GC::Sprite>(nave, sprite, sprite_src, sprite_dest);
  reg.emplace<GC::Collidable>(nave, false, sprite_dest);
  reg.emplace<GC::Player>(nave);
  return nave;
}

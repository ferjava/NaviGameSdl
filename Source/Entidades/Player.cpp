#include "../Componentes/GameTags.hpp"
#include "../Componentes/Graficos.hpp"
#include "../Componentes/transformadas.hpp"
#include "Entidades.hpp"
#include "entt/entt.hpp"
void Factory::createPlayer(entt::registry &reg, GameContext &ctx) {
  auto sprite = ctx.tm->getTexture("assets/images/Naveplayer1.png");
  SDL_FRect sprite_src{300.0f, 0.0f, 100.0f, 90.0f};
  SDL_FRect sprite_dest{0.0f, 0.0f, sprite_src.w / 2, sprite_src.h / 2};
  auto nave = reg.create();

  reg.emplace<GC::Posicion>(nave, ctx.pantalla.w / 2, ctx.pantalla.h / 2);
  reg.emplace<GC::Velocidad>(nave, 0.0f, 0.0f);
  reg.emplace<GC::Sprite>(nave, sprite, sprite_src, sprite_dest);
  reg.emplace<GC::Player>(nave);
}

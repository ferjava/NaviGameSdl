#include "../Componentes/Componentes.hpp"
#include "Entidades.hpp"
#include "SDL3/SDL_log.h"
#include "entt/entt.hpp"

float VELOCIDAD_BALA = 200.0f;
entt::entity Factory::creatBullet(entt::registry &reg, GameContext &ctx) {

  auto _balasp = ctx.tm->getTexture("assets/images/bala.png");
  if (!_balasp)
    SDL_Log("Error al cargar la imagen de bala ");
  SDL_FRect src{0, 0, 32.0f, 32.0f};
  SDL_FRect dest{0, 0, 6.0f, 6.0f};
  auto bala = reg.create();
  reg.emplace<GC::Sprite>(bala, _balasp, src, dest);
  reg.emplace<GC::Posicion>(bala, 0.0f, 0.0f);
  reg.emplace<GC::Velocidad>(bala, 0.0f, -VELOCIDAD_BALA);
  reg.emplace<GC::Bala>(bala); // WARNING: En las versiones anteriores falta

  return bala;
}

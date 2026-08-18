#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/GameConfig.hpp"
#include "entt/entity/fwd.hpp"
#include <algorithm>
#include <vector>
void boss_shoot(entt::entity &enti, entt::registry &reg, GameContext &ctx) {
  // TODO: Cuando el boss dispare
}
void boss_colision(entt::registry &reg, entt::entity &enti,
                   std::vector<entt::entity> &destroyer, GameContext &ctx) {
  // TODO: Cuando el Boss choque
}

entt::entity Factory::creatEnemyBoss(entt::registry &reg, GameContext &ctx) {
  // cargamos el primer grafic
  // at
  // at
  using namespace Game::Enemy;

  // Creando el vector de posiciones de la pantalla
  std::vector<GC::Posicion> _pos = {
      {ctx.pantalla.w * 1 / 4, 0.0f},
      {ctx.pantalla.w * 1 / 4, ctx.pantalla.h * 1 / 4},

      {ctx.pantalla.w * 1 / 4, ctx.pantalla.h * 1 / 2},
      {ctx.pantalla.w * 1 / 2, ctx.pantalla.h * 1 / 2},
      {ctx.pantalla.w * 1 / 2, ctx.pantalla.h * 1 / 3}};

  BOSS._pos = _pos;
  auto sprite = ctx.tm->getTexture("assets/images/boss.png");
  // Cargamos el sprite 0 de la animacion
  SDL_FRect area_impact(
      (float)sprite->w / 2 - 30.0f, (float)sprite->h, 60.0f,
      -60.0f); // en medio  la parte de abajo del avion un recuadro de 60x60
  SDL_FRect rect_dest{0.0f, 0.0f, Game::Enemy::BOSS._sprite_src[0].w,
                      Game::Enemy::BOSS._sprite_src[0].h};
  auto boss = reg.create();
  reg.emplace<GC::Enemy>(boss); // Es un enemigo
  reg.emplace<GC::Boss>(boss);  // Tambien es un boss
  reg.emplace<GC::Posicion>(boss, BOSS._pos[0].X,
                            BOSS._pos[0].Y);   // poscion 0 del vector
  reg.emplace<GC::Velocidad>(boss, BOSS._vel); // Velocidad
  reg.emplace<GC::Sprite>(boss, sprite, BOSS._sprite_src[0], rect_dest);
  reg.emplace<::IA::Moviment>(boss, BOSS._pos); // Vector de posiciones
  reg.emplace<::IA::Live>(boss, BOSS._live);
  reg.emplace<::IA::Dispara>(boss, BOSS.TIME_TO_SHOOT, BOSS.DADO_VALOR,
                             boss_shoot);
  reg.emplace<GC::Collidable>(boss, area_impact, boss_colision);
  SDL_Log("Boss Creado ");
  return boss;
}
void Acciones::moveBoss(entt::registry &reg, GameContext &ctx, int index) {
  // TODO: Aqui hacemos toda la animacion del movimiento

  // 1. Cargamos  la vista con la tags posicion , moviment y sprite que
  // modificaremos
  auto view = reg.view<GC::Boss, GC::Posicion, GC::Sprite, ::IA::Moviment>();
  for (auto enti : view) {
    auto &pos = reg.get<GC::Posicion>(enti);
    auto &sp = reg.get<GC::Sprite>(enti);
    auto &movi = reg.get<::IA::Moviment>(enti);

    // Comprobamos que la poscion actual es igual la poscion de cambio de
    // movimiento
    // if (pos.X == movi.destino.back().X && pos.Y == movi.destino.back().Y) {
    // Cambiamos la imagen a la que corresponda
    // ESTO NO SE QUE VA PASAR

    sp.source = Game::Enemy::BOSS._sprite_src[index];
    sp.dest = {0.0f, 0.0f, sp.source.w, sp.source.h};

    SDL_Log("INDICE ACTUAL %d ", index);
  }
}

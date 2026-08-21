#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/GameConfig.hpp"
#include "Utils/Utils.hpp"
#include "entt/entity/fwd.hpp"
#include <algorithm>
#include <vector>
void boss_shoot(entt::entity &enti, entt::registry &reg, GameContext &ctx) {

  // TODO: Cuando el boss dispare
  GC::Velocidad bala_velo = {-200, 200};
  for (int i = 0; i < 5; i++) {
    bala_velo.Vx = bala_velo.Vx + 100;
    auto bala = Factory::createBullet(reg, ctx, bala_velo);
    auto &pos_bala = reg.get<GC::Posicion>(bala);
    auto &pos_enti = reg.get<GC::Posicion>(enti);
    pos_bala.X = pos_enti.X + Game::Enemy::BOSS._sprite_src.back().w / 2;
    pos_bala.Y = pos_enti.Y + Game::Enemy::BOSS._sprite_src.back().h - 10;
  }
}
void boss_colision(entt::registry &reg, entt::entity &enti,
                   std::vector<entt::entity> &destroyer, GameContext &ctx) {
  // TODO: Cuando el Boss choque
  // 1.Comprobar que esta vivo
  auto &living = reg.get<IA::Live>(enti);

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
    auto &enti_pos = reg.get<GC::Posicion>(enti);
    explo_pos = enti_pos; // Colocamos la esplosion en lugar de la nave
                          // Game::Player::SCORE += 500;
    ctx.elimina_entidad.push_back(enti);
  }
}

entt::entity Factory::creatEnemyBoss(entt::registry &reg, GameContext &ctx) {
  // cargamos el primer grafic
  // at
  // at
  using namespace Game::Enemy;

  // Creando el vector de posiciones de la pantalla
  std::vector<GC::Posicion> _pos = {
      //{ctx.pantalla.w * 1 / 4, 0.0f},
      {ctx.pantalla.w * 1 / 4, ctx.pantalla.h * 1 / 4},

      {ctx.pantalla.w * 1 / 4, ctx.pantalla.h * 1 / 2},
      {ctx.pantalla.w * 1 / 2, ctx.pantalla.h * 1 / 2},
      {ctx.pantalla.w * 1 / 2, ctx.pantalla.h * 1 / 3}};

  BOSS._pos = _pos;
  auto sprite = ctx.tm->getTexture("assets/images/boss.png");
  // Cargamos el sprite 0 de la animacion

  SDL_FRect rect_dest{0.0f, 0.0f, Game::Enemy::BOSS._sprite_src[0].w,
                      Game::Enemy::BOSS._sprite_src[0].h};
  SDL_FRect area_impact(
      rect_dest.w / 2 - 30.0f, rect_dest.h, 60.0f,
      -20.0f); // en medio  la parte de abajo del avion un recuadro de 60x60
  auto boss = reg.create();
  reg.emplace<GC::Enemy>(boss); // Es un enemigo
  reg.emplace<GC::Boss>(boss);  // Tambien es un boss
  reg.emplace<GC::Posicion>(boss, ctx.pantalla.w * 1 / 4,
                            -10.0f);           // poscion 0 del vector
  reg.emplace<GC::Velocidad>(boss, BOSS._vel); // Velocidad
  reg.emplace<GC::Sprite>(boss, sprite, BOSS._sprite_src[0], rect_dest);
  reg.emplace<::IA::Moviment>(boss, BOSS._pos); // Vector de posiciones
  reg.emplace<::IA::Live>(boss, BOSS._live);
  // reg.emplace<::IA::Dispara>(boss, BOSS.TIME_TO_SHOOT, BOSS.DADO_VALOR,
  // boss_shoot);
  reg.emplace<GC::Collidable>(boss, area_impact, boss_colision);
  SDL_Log("Boss Creado ");
  return boss;
}
void Acciones::moveBoss(entt::registry &reg, GameContext &ctx) {
  // TODO: Aqui hacemos toda la animacion del movimiento

  // 1. Cargamos  la vista con la tags posicion , moviment y sprite que
  // modificaremos
  auto view = reg.view<GC::Boss, GC::Posicion, GC::Sprite, ::IA::Moviment>();
  for (auto enti : view) {
    auto &pos = reg.get<GC::Posicion>(enti);
    auto &sp = reg.get<GC::Sprite>(enti);
    auto &movi = reg.get<::IA::Moviment>(enti);
    auto &coli = reg.get<GC::Collidable>(enti);

    static int index = 0;
    bool change = reg.all_of<::IA::PosChange>(enti);
    if (change) {
      if (index != movi.destino.size() - 1) {
        index++;
      } else {
        if (movi.repeat)
          index = 0;
      }
    }
    if (reg.all_of<GC::Boss_changed>(enti)) {
      using namespace Game::Enemy;
      sp.source = Game::Enemy::BOSS
                      ._sprite_src[Game::Enemy::BOSS._sprite_src.size() - 1];

    } else {

      if (index > Game::Enemy::BOSS._sprite_src.size() - 1) {

        sp.source = Game::Enemy::BOSS
                        ._sprite_src[Game::Enemy::BOSS._sprite_src.size() - 1];
        sp.dest = {0.0f, 0.0f, sp.source.w, sp.source.h};

      } else {
        sp.source = Game::Enemy::BOSS._sprite_src[index];
        sp.dest = {0.0f, 0.0f, sp.source.w, sp.source.h};
      }
    }

    if (reg.all_of<::IA::MoveEnd>(enti) && change &&
        !reg.all_of<GC::Boss_changed>(enti)) {
      reg.emplace_or_replace<GC::Boss_changed>(enti);
      std::vector<GC::Posicion> swap;
      for (int i = 0; i < 6; i++) {
        GC::Posicion new_pos;
        int x = Utils::Dado(Pantalla_W / 4, Pantalla_W * 3 / 4);
        int y = Utils::Dado(10, Pantalla_H / 3);
        new_pos = {(float)x, (float)y};
        swap.push_back(new_pos);
      }
      pos.X = movi.destino.back().X;
      pos.Y = movi.destino.back().Y;
      sp.dest = {0.0f, 0.0f, sp.source.w, sp.source.h};

      reg.emplace_or_replace<::IA::Moviment>(enti, swap, true);
      reg.emplace<::IA::Dispara>(enti, Game::Enemy::BOSS.TIME_TO_SHOOT,
                                 Game::Enemy::BOSS.DADO_VALOR, boss_shoot);
    }
  }
}

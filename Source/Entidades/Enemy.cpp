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

  auto &islive = reg.get<IA::Live>(entidad);
  if (islive.is_live) {
    SDL_Log(" Colsion en Enemigo");
    auto exploent = Factory::createExplosion(reg, ctx);
    auto &pos = reg.get<GC::Posicion>(exploent);
    pos = reg.get<GC::Posicion>(entidad);
    Game::Player::SCORE += 200;
    islive.is_live = false;
    destroyer.push_back(entidad);
    ctx.elimina_entidad.push_back(entidad);
  }
}
void unabala(entt::entity &entidad, entt::registry &reg, GameContext &ctx) {
  auto velo = GC::Velocidad{0.0f, 200.0f};
  auto bala = Factory::createBullet(reg, ctx, velo);
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
/// @brief Crea un grupo de enemigos de l tipo straigth en una salida 1 al 6
///
void Factory::createGroupEnemysStraight(entt::registry &reg, GameContext &ctx,
                                        int pos_salida) {

  using namespace Game::Enemy::Straight;
  auto sprite = ctx.tm->getTexture("assets/images/enemigos.png");
  // cambiamos datos segun salida

  SDL_FRect origen{MOVE_RIGHT, Game::Enemy::TEXTURE_H * 2.0f,
                   Game::Enemy::TEXTURE_W, Game::Enemy::TEXTURE_H};

  float pos_X;
  float pos_Y;
  float vel_X;
  float vel_Y;
  int eje_X;
  int eje_Y;
  enum eje {
    LESSTEXTURA = -1,
    NOTEXTURA = 0,
    ADDTEXTURA = 1
  }; // Multiplicando por la Textura hacamos que las naves se sigan unas a otras
  // posx = posx + TEXTURA*eje (LESS resta Textura en ese eje , NOTeXTURA no add
  // TEXTURA En ese je ,ADD add textura en ese eje  )
  if (pos_salida == 0) {
    SDL_Log("ERROR NO PUNTO DE SALIDA ");
    return;
  }
  // SALIDA  CENTRO_IZQUIEDA
  if (pos_salida == 1) {
    pos_X = 0.0f; //-(Game::Enemy::TEXTURE_W + Game::Enemy::TEXTURE_W);
    eje_X = eje::LESSTEXTURA;
    pos_Y = ctx.pantalla.h / 3;
    eje_Y = eje::NOTEXTURA;
    vel_X = VELOCIDAD_X;
    vel_Y = 0.0f;
    origen.x = MOVE_RIGHT;
    origen.y = Game::Enemy::TEXTURE_H * 2.0f;
  }
  if (pos_salida == 2) {

    pos_X = 0.0f; //- (Game ::Enemy::TEXTURE_W + Game::Enemy::TEXTURE_W);
    eje_X = eje::LESSTEXTURA;
    pos_Y = 0.0f; //- (Game::Enemy::TEXTURE_H + Game::Enemy::TEXTURE_H);
    eje_Y = eje::LESSTEXTURA;
    vel_X = VELOCIDAD_X;
    vel_Y = VELOCIDAD_Y;
    // Corresponde al elemento 15 del spritesheet  (x 6 , y 3 )
    origen.x = MOVE_RIGHT;                 // Elemento 6
    origen.y = Game::Enemy::TEXTURE_H * 3; // fila 3
  }
  if (pos_salida == 3) {

    pos_X = ctx.pantalla.w / 2 - Game::Enemy::TEXTURE_W;
    eje_X = eje::NOTEXTURA;
    pos_Y = 0.0f;
    eje_Y = eje::LESSTEXTURA;
    vel_X = 0.0f;
    vel_Y = VELOCIDAD_Y;
    origen.x = MOVE_CENTER;                //(x=3 en spritesheet)
    origen.y = Game::Enemy::TEXTURE_H * 3; // y=3 fila 3
  }
  if (pos_salida == 4) {

    pos_X = ctx.pantalla.w / 2 + Game::Enemy::TEXTURE_W;
    eje_X = eje::NOTEXTURA;
    pos_Y = 0.0f; //-(Game::Enemy::TEXTURE_H + Game::Enemy::TEXTURE_H);
    eje_Y = eje::LESSTEXTURA;
    vel_X = 0.0f;
    vel_Y = VELOCIDAD_Y;
    origen.x = MOVE_CENTER;                //(x=3 en spritesheet)
    origen.y = Game::Enemy::TEXTURE_H * 3; // y=3 fila 3
  }
  if (pos_salida == 5) {

    pos_X = ctx.pantalla.w + (Game::Enemy::TEXTURE_W + Game::Enemy::TEXTURE_W);
    eje_X = eje::ADDTEXTURA;
    pos_Y = 0.0f; //-(Game::Enemy::TEXTURE_H + Game::Enemy::TEXTURE_H);
    eje_Y = eje::LESSTEXTURA;
    vel_X = +VELOCIDAD_X;
    vel_Y = +VELOCIDAD_Y;
    origen.x = MOVE_LEFT;                  // x= 0 primero del spritesheet
    origen.y = Game::Enemy::TEXTURE_H * 3; // y= 3 fila 3
  }
  if (pos_salida == 6) {
    pos_X =
        ctx.pantalla.w; // (Game::Enemy::TEXTURE_W + Game::Enemy::TEXTURE_W);
    eje_X = eje::ADDTEXTURA;
    pos_Y = ctx.pantalla.h / 3;
    eje_Y = eje::NOTEXTURA;
    vel_X = +VELOCIDAD_X;
    vel_Y = 0.0f;
    origen.x = MOVE_LEFT;
    origen.y = Game::Enemy::TEXTURE_H * 2.0f;
  }

  SDL_FRect desti{0.0f, 0.0f, origen.w * 2, origen.h * 2};
  for (int i = 0; i < Grupo; i++) {
    auto nave_enemiga = reg.create();
    reg.emplace<GC::Posicion>(
        nave_enemiga, pos_X = pos_X + (2 * Game::Enemy::TEXTURE_W * eje_X),
        pos_Y = pos_Y + (2 * Game::Enemy::TEXTURE_H * eje_Y));

    reg.emplace<GC::Velocidad>(nave_enemiga, vel_X, vel_Y);
    reg.emplace<GC::Sprite>(nave_enemiga, sprite, origen, desti);
    reg.emplace<GC::Collidable>(nave_enemiga, false, desti, colisionEnemy);
    reg.emplace<IA::Dispara>(nave_enemiga, TIME_TO_SHOOT, VALOR_MAX_DISPARO,
                             unabala);
    reg.emplace<IA::Live>(nave_enemiga);
    reg.emplace<GC::Enemy>(nave_enemiga);
  }
}

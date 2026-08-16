#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/GameConfig.hpp"
#include "../Game/NaviGame.hpp"
#include "Sistemas.hpp"
#include "entt/entity/fwd.hpp"
void Sistema::Movimiento(entt::registry &reg, float dt) {
  auto view = reg.view<GC::Posicion,
                       GC::Velocidad>(
      entt::exclude<::IA::Moviment>); // Excluye las de movimiento autamitca
  std::vector<entt::entity> EntidadParaDestruir;
  for (auto enti : view) {
    auto &pos = view.get<GC::Posicion>(enti);
    auto &vel = view.get<GC::Velocidad>(enti);

    pos.X += vel.Vx * dt;
    pos.Y += vel.Vy * dt;
    // Comprobamos las balas
    if (reg.all_of<GC::BalaPlayer>(enti)) {
      if (pos.Y <= 0) {
        EntidadParaDestruir.push_back(enti);
      }
    }

    // if (reg.all_of<GC::Raptor>(enti)) {
    // Acciones::moveRaptor(reg, dt);
    //}

    if (reg.all_of<GC::Enemy, GC::Straight>(enti)) {
      if (pos.X <= 0) {
        // TODO: Mueve hacia la derecha
        auto &sp = reg.get<GC::Sprite>(enti);
        sp.source.x = Game::Enemy::MOVE_RIGHT;
        vel.Vx = Game::Enemy::VELOCIDAD_X * 2;

      } else if (pos.X + Game::Enemy::TEXTURE_W >= NaviGame::ctx.pantalla.w) {

        // TODO: Mueve hacia la izquierda
        auto &sp = reg.get<GC::Sprite>(enti);
        sp.source.x = Game::Enemy::MOVE_LEFT;
        vel.Vx = -Game::Enemy::VELOCIDAD_X * 2;
      }
      // Borrar lso que superan el limite inferior
      if (pos.Y + Game::Enemy::TEXTURE_H >= NaviGame::ctx.pantalla.h) {
        EntidadParaDestruir.push_back(enti);
      }
      if (pos.Y <= 0 &&
          vel.Vy < 0) // Limpiamos si la nave supera el limite superior
      {
        EntidadParaDestruir.push_back(enti);
      }
      // BUG:

      // Desde izquierda al centro
      if (pos.X + Game::Enemy::TEXTURE_W >= NaviGame::ctx.pantalla.w / 2 ||
          pos.Y + Game::Enemy::TEXTURE_H >= NaviGame ::ctx.pantalla.h / 2) {
        // Los que aparecen por el centro de pantalla desde la izquierda
        if (vel.Vx > 0 && vel.Vy == 0) {
          // cambiamos el grafico
          auto &sp = reg.get<GC::Sprite>(enti);
          sp.source.x = Game::Enemy::Straight::MOVE_RIGHT +
                        Game::Enemy::TEXTURE_W; // pos x = 1 del spritehset
          sp.source.y = Game::Enemy::TEXTURE_H * 1.0f;
          vel.Vx = -Game::Enemy::Straight::VELOCIDAD_X;
          vel.Vy = -Game::Enemy::Straight::VELOCIDAD_Y / 2;
        }

        // Aparacen por las esquina superior izquierda
        else if (vel.Vx > 0 && vel.Vy > 0) {

          auto &sp = reg.get<GC::Sprite>(enti);
          sp.source.x =
              Game::Enemy::Straight::MOVE_RIGHT; // pos x = 1 del spritehset
          sp.source.y = Game::Enemy::TEXTURE_W * 2.0f;
          vel.Vx = Game::Enemy::Straight::VELOCIDAD_X;
          vel.Vy = -Game::Enemy::Straight::VELOCIDAD_Y / 10;
        } // Aparecen por el centro superior de la pantalla
        else if (vel.Vx == 0 && vel.Vy > 0 &&
                 pos.Y >= NaviGame::ctx.pantalla.h / 2) {

          auto &sp = reg.get<GC::Sprite>(enti);
          sp.source.x =
              Game::Enemy::Straight::MOVE_LEFT; // pos x = 1 del spritehset
          sp.source.y = Game::Enemy::TEXTURE_W * 2.0f;
          vel.Vx = -Game::Enemy::Straight::VELOCIDAD_X;
          vel.Vy = -Game::Enemy::Straight::VELOCIDAD_Y / 10;
        }
        // Aparecen por la posicion esquina superior derecha
        else if (vel.Vx < 0 && vel.Vy > 0 &&
                 pos.X <= NaviGame::ctx.pantalla.w * 2 / 3) {
          auto &sp = reg.get<GC::Sprite>(enti);
          sp.source.x = Game::Enemy::Straight::MOVE_LEFT;
          sp.source.y = Game::Enemy::TEXTURE_H * 2;
          vel.Vx = -Game::Enemy::Straight::VELOCIDAD_X;
          vel.Vy = 0.0f;
        }

      } // BUG:
    }
    // Borramos las balas que se salen de la pantalla
    if (reg.all_of<GC::BalaEnemy>(enti)) {
      if (pos.Y + Game::Bala::TAMANO_BALA >= NaviGame::ctx.pantalla.h) {
        EntidadParaDestruir.push_back(enti);
      }
    }
  }
  for (auto entidad : EntidadParaDestruir) {
    reg.destroy(entidad);
    // SDL_Log("Bala destruida ");
  }
}

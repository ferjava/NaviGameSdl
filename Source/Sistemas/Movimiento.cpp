#include "../Componentes/Componentes.hpp"
#include "../Game/GameConfig.hpp"
#include "../Game/NaviGame.hpp"
#include "Sistemas.hpp"
#include "entt/entity/fwd.hpp"
void Sistema::Movimiento(entt::registry &reg, float dt) {
  auto view = reg.view<GC::Posicion, GC::Velocidad>();
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
    if (reg.all_of<GC::Enemy>(enti)) {
      if (pos.X <= 0) {
        // TODO: Mueve hacia la derecha
        auto &sp = reg.get<GC::Sprite>(enti);
        sp.source.x = Game::Enemy::MOVE_RIGHT;
        vel.Vx = Game::Enemy::VELOCIDAD_X;

      } else if (pos.X + Game::Enemy::TEXTURE_W >= NaviGame::ctx.pantalla.w) {

        // TODO: Mueve hacia la izquierda
        auto &sp = reg.get<GC::Sprite>(enti);
        sp.source.x = Game::Enemy::MOVE_LEFT;
        vel.Vx = -Game::Enemy::VELOCIDAD_X;
      }
      // Borrar lso que superan el limite inferior
      else if (pos.Y + Game::Enemy::TEXTURE_H >= NaviGame::ctx.pantalla.h) {
        EntidadParaDestruir.push_back(enti);
      }
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

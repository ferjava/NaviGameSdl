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
        auto &sp = reg.get<GC::Sprite>(enti);
        sp.source.x = Game::Enemy::MOVE_RIGHT;
        vel.Vx = Game::Enemy::VELOCIDAD_X;

      } else if (pos.X + Game::Enemy::TEXTURE_W >= NaviGame::ctx.pantalla.w) {

        auto &sp = reg.get<GC::Sprite>(enti);
        sp.source.x = Game::Enemy::MOVE_LEFT;
        vel.Vx = -Game::Enemy::VELOCIDAD_X;
      }
    }
  }
  for (auto entidad : EntidadParaDestruir) {
    reg.destroy(entidad);
    // SDL_Log("Bala destruida ");
  }
}

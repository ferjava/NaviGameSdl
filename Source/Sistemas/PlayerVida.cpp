#include "../Componentes/Componentes.hpp"
#include "../Game/GameConfig.hpp"
#include "../Game/GameContex.hpp"
#include "../Sistemas/Sistemas.hpp"
float livestart = 0.0f;
void Sistema::IA::PlayerVida(entt::registry &reg, float dt, GameContext ctx) {
  auto view = reg.view<GC::Posicion, GC::Velocidad, GC::Player, ::IA::Live,
                       GC::Collidable>();
  for (auto enti : view) {
    auto &live = view.get<::IA::Live>(enti);
    auto &vel = view.get<GC::Velocidad>(enti);
    auto &pos = view.get<GC::Posicion>(enti);
    auto &choque = view.get<GC::Collidable>(enti);
    if (!live.is_live) {
      livestart += dt;
      if (livestart >= 2.0f) {
        choque.isCollidable = true;
        live.is_live = true;
        livestart = 0.0f;
        vel.Vx = Game::Player::SPEED;
        vel.Vy = Game::Player::SPEED;
      } else {
        choque.isCollidable = false;
        vel.Vx = 0.0f;
        vel.Vy = -200.0f;
      }
    }
  }
}

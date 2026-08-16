#include "Sistemas.hpp"

using namespace Sistema::IA;

void Sistema::IA::UpdateSystemIA(entt::registry &reg, float dt,
                                 GameContext &ctx) {
  Sistema::IA::UpdateTimerSystem(reg, dt);
  Sistema::IA::PlayerVida(reg, dt, ctx);
  Sistema::IA::GeneraBalas(reg, dt);
  Sistema::IA::MoviAutomatico(reg, dt, ctx);
}

#include "../Componentes/Componentes.hpp"
#include "Sistemas.hpp"
///@brief:Sistema actualiza  todos los componentes temporizadores
///

void Sistema::IA::UpdateTimerSystem(entt::registry &reg, float dt) {
  // 1. Limpiamos las  etiquitas de temporizadores
  auto expired_time = reg.view<::Utils::TimeExpiredTag>();
  reg.destroy(expired_time.begin(), expired_time.end());
  // 2. Procesamos todas las entidades temporizadores
  auto view = reg.view<Utils::Temporizador>();
  for (auto enti : view) {
    auto time = reg.get<Utils::Temporizador>(enti);
    if (time.Terminado)
      continue;
    time.tRestante -= dt;
    if (time.tRestante > 0.0f) {
      time.tRestante = 0.0f;
      if (time.Repite) {
        // reinicia el contador
        time.tRestante = time.tDuracion;

      } else {
        time.Terminado = true;
      }
      reg.emplace_or_replace<Utils::TimeExpiredTag>(enti);
      // Si hemos definido el callback llamalo
      if (time.on_timeout) // Si no es nullptr
      {
        time.on_timeout(enti);
      }
    }
  }
}

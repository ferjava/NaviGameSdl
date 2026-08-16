#include "../Componentes/Inteligencia.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Game/GameConfig.hpp"
#include "../Game/NaviGame.hpp"
#include "Sistemas.hpp"
#include <random>

void Sistema::IA::GeneraBalas(entt::registry &reg, float dt) {

  /* std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<int> caras(1, 10);*/
  auto view = reg.view<::IA::Dispara>();
  for (auto enti : view) {
    auto &disp = view.get<::IA::Dispara>(enti);
    // lanza dado
    disp.lanzadado += dt; // teporizador
    if (!disp.ha_disparado) {
      // Tiempo para disparar
      if (disp.lanzadado >= disp.turno_time) {
        int res = Utils::Dado(1, 10);
        SDL_Log("El numeor generado es :%d", res);
        // Dispara si res
        if (res <= disp.dado_disparo) {
          SDL_Log("Disparo %d ", res);
          disp.disparo(enti, reg, NaviGame::ctx);
          disp.ha_disparado = true;
          disp.lanzadado = 0.0f;
        } else {
          disp.ha_disparado = false;
          disp.lanzadado = 0.0f;
        }
      }
    }
    // vuelve disparar
    if (disp.lanzadado >= Game::Enemy::Straight::TIME_DO_SHOOT &&
        disp.ha_disparado) {
      disp.ha_disparado = false;
      disp.lanzadado = 0.0f;
    }
  }
}

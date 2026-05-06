#include "../Componentes/GameTags.hpp"
#include "../Componentes/transformadas.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_scancode.h"
#include "Sistemas.hpp"

void Sistema::Entrada_Teclado(entt::registry &reg) {
  auto view = reg.view<GC::Player, GC::Velocidad>();
  const bool *keys = SDL_GetKeyboardState(nullptr);
  for (auto entity : view) {
    auto &vel = view.get<GC::Velocidad>(entity);
    float speed = 200.0f;
    vel.Vx = 0.0f;
    vel.Vy = 0.0f;
    if (keys[SDL_SCANCODE_UP])
      vel.Vy = -speed;
    if (keys[SDL_SCANCODE_DOWN])
      vel.Vy = speed;
    if (keys[SDL_SCANCODE_RIGHT])
      vel.Vx = speed;
    if (keys[SDL_SCANCODE_LEFT])
      vel.Vx = -speed;
  }
};

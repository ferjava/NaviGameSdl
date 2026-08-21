#pragma once
#include "../Entidades.hpp"
#include "SDL3/SDL.h"

namespace Utils {

void f_Blink(SDL_Texture *sprite, float time, float dt, int alpha = 100);
bool Move_To(GC::Posicion &pos_ini, GC::Posicion &pos_final, GC::Velocidad &vel,
             float dt);
int Dado(int Valor_min, int Valor_max);

struct CountDown {
  float time_actual = 0.0f;
  float repite = false;
  bool actualizar(float target_time, float dt);
  void reiniciar();
};

struct Blink {
  Utils::CountDown tempo;
  int On_alpha = 255;
  int Off_alpha = 1;
  bool On_flag = false;
  void update(SDL_Texture *sprite, float timer_change, float dt);
};
} // namespace Utils

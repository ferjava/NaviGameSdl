#include "Utils.hpp"

bool Utils::CountDown::actualizar(float time, float dt) {
  time_actual += dt;
  if (time_actual >= time) {
    if (repite) {
      reiniciar();
    }
    return true;
  }
  return false;
}
void Utils::CountDown::reiniciar() { time_actual = 0.0f; }

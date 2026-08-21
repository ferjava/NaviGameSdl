#include "Utils.hpp"

namespace blink {
bool blink = false;
float actual_time = 0.0f;
} // namespace blink
//
// @brief : Esta funcion hace que una textura se oscurezca cada cierto tiempo
// @param sprite = SDL_Texture que haremos que se oscurezca
// @param time_blinked = Tiempo que esta oscurezca
// @param  dt contiene float que contiene la dt del tiempo
// @oaram alpha valor has ta el que se oscurece 0 (oscuro ) 255 brillo
void Utils::f_Blink(SDL_Texture *sprite, float time_blinked, float dt,
                    int alpha) {
  blink::actual_time += dt;
  if (blink::actual_time >= time_blinked) {
    if (!blink::blink) {
      blink::blink = true;
      blink::actual_time = 0.0f;
    } else {
      blink::blink = false;
      blink::actual_time = 0.0f;
    }
  }
  if (blink::blink)
    SDL_SetTextureAlphaMod(sprite, alpha);
  else
    SDL_SetTextureAlphaMod(sprite, 255);
}

void Utils::Blink::update(SDL_Texture *sprite, float time_change, float dt) {

  if (tempo.actualizar(time_change, dt)) {
    if (On_flag) {
      On_flag = false;
    } else {
      On_flag = true;
    }
  }
  if (On_flag) {
    SDL_SetTextureAlphaMod(sprite, On_alpha);
  } else {
    SDL_SetTextureAlphaMod(sprite, Off_alpha);
  }
}

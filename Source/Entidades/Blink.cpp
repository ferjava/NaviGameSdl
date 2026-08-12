#include "Entidades.hpp"
bool blink = false;
float actual_time = 0.0f;
void Efecto::Blink(SDL_Texture *sprite, float time_blinked, GameContext &ctx,
                   int alpha) {
  actual_time += *ctx.delta_time;
  if (actual_time >= time_blinked) {
    if (!blink) {
      blink = true;
      actual_time = 0.0f;
    } else {
      blink = false;
      actual_time = 0.0f;
    }
  }
  if (blink)
    SDL_SetTextureAlphaMod(sprite, alpha);
  else
    SDL_SetTextureAlphaMod(sprite, 255);
}

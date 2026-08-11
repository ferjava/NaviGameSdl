#include "../../Componentes/Componentes.hpp"
#include "../../Game/NaviGame.hpp"
#include "Entidades.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
entt::entity Factory::Title::createPress(entt::registry &reg,
                                         GameContext &ctx) {
  auto font = TTF_OpenFont("assets/fonts/Marker Felt.ttf", 30.0f);
  if (!font)
    SDL_Log("error al cargar la fuente de texto");
  // Creamos la surface
  SDL_Color blanco = {255, 255, 255, 255};
  auto text = TTF_RenderText_Blended(font, "Press Space", 0, blanco);
  if (text) {
    auto presspace = SDL_CreateTextureFromSurface(NaviGame::ctx.render, text);
    SDL_SetTextureBlendMode(presspace, SDL_BLENDMODE_BLEND);
    NaviGame::ctx.tm->Add(presspace, "start");
    SDL_DestroySurface(text);

    if (!presspace) {
      SDL_Log("Error al crear el texto");
    }
  }
  TTF_CloseFont(font);
  // Aqui empezamos con entt
  auto score_sprite = NaviGame::ctx.tm->getTexture("start");
  auto score_source = SDL_FRect{0, 0, (float)score_sprite.get()->w,
                                (float)score_sprite.get()->h};
  auto _presspace = reg.create();

  reg.emplace<GC::Posicion>(
      _presspace, ctx.pantalla.w / 2 - (float)score_sprite.get()->w / 2,
      ctx.pantalla.h * 2 / 3 - (float)score_sprite.get()->h / 2);
  reg.emplace<GC::Sprite>(_presspace, score_sprite, score_source);
  reg.emplace<::Title::PressStart>(_presspace);
  return _presspace;
}

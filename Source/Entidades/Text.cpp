#include "../Componentes/GameTags.hpp"
#include "../Componentes/Graficos.hpp"
#include "../Componentes/transformadas.hpp"
#include "../Game/GameConfig.hpp"
#include "../Game/NaviGame.hpp"
#include "Entidades.hpp"
#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "Version.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include <string>
entt::entity Factory::createVersionText(entt::registry &reg, GameContext &ctx) {
  // Creamos el Texto
  auto font = TTF_OpenFont("assets/fonts/Marker Felt.ttf", 12.0f);
  if (!font)
    SDL_Log("error al cargar la fuente de texto");
  // Creamos la surface
  SDL_Color blanco = {255, 255, 255, 255};
  auto text =
      TTF_RenderText_Blended(font, "version:" VERSION_STRING, 0, blanco);
  if (text) {
    auto textversion = SDL_CreateTextureFromSurface(NaviGame::ctx.render, text);
    SDL_SetTextureBlendMode(textversion, SDL_BLENDMODE_BLEND);
    NaviGame::ctx.tm->Add(textversion, "textversion");
    SDL_DestroySurface(text);

    if (!textversion) {
      SDL_Log("Error al crear el texto");
    }
  }
  TTF_CloseFont(font);
  // Aqui empezamos con entt
  auto textversion = NaviGame::ctx.tm->getTexture("textversion");
  auto textsourc =
      SDL_FRect{0, 0, (float)textversion.get()->w, (float)textversion.get()->h};
  auto _textversion = reg.create();

  reg.emplace<GC::Posicion>(_textversion, ctx.pantalla.w - textversion->w,
                            ctx.pantalla.h - textversion->h);
  reg.emplace<GC::Velocidad>(_textversion, 0.0f, 0.0f);
  reg.emplace<GC::Sprite>(_textversion, textversion, textsourc);
  return _textversion;
}
// Funcion para crear el Score del jugador en la pantalla
entt::entity Factory::createScoreText(entt::registry &reg, GameContext &ctx) {
  // Creamos el Texto
  auto font = TTF_OpenFont("assets/fonts/Marker Felt.ttf", 40.0f);
  if (!font)
    SDL_Log("error al cargar la fuente de texto");
  // Creamos la surface
  SDL_Color blanco = {255, 255, 255, 255};
  auto s_score = "score:" + std::to_string(Game::Player::SCORE);
  auto text = TTF_RenderText_Blended(font, s_score.c_str(), 0, blanco);
  if (text) {
    auto score = SDL_CreateTextureFromSurface(NaviGame::ctx.render, text);
    SDL_SetTextureBlendMode(score, SDL_BLENDMODE_BLEND);
    NaviGame::ctx.tm->Add(score, "score");
    SDL_DestroySurface(text);

    if (!score) {
      SDL_Log("Error al crear el texto");
    }
  }
  TTF_CloseFont(font);
  // Aqui empezamos con entt
  auto score_sprite = NaviGame::ctx.tm->getTexture("score");
  auto score_source = SDL_FRect{0, 0, (float)score_sprite.get()->w,
                                (float)score_sprite.get()->h};
  auto _score = reg.create();

  reg.emplace<GC::Posicion>(
      _score, ctx.pantalla.w / 2 - (float)score_sprite.get()->w / 2,
      0.0f + score_sprite.get()->h);
  reg.emplace<GC::Velocidad>(_score, 0.0f, 0.0f);
  reg.emplace<GC::Sprite>(_score, score_sprite, score_source);
  return _score;
}
// Funcion para crear el  Game Over
entt::entity Factory::createGameOver(entt::registry &reg, GameContext &ctx) {
  auto font = TTF_OpenFont("assets/fonts/Marker Felt.ttf", 100.0f);
  if (!font)
    SDL_Log("error al cargar la fuente de texto");
  // Creamos la surface
  SDL_Color rojo = {255, 0, 0, 255};
  auto text = TTF_RenderText_Blended(font, "ESTAS MUERTO", 0, rojo);
  if (text) {
    auto gameover = SDL_CreateTextureFromSurface(NaviGame::ctx.render, text);
    SDL_SetTextureBlendMode(gameover, SDL_BLENDMODE_BLEND);
    NaviGame::ctx.tm->Add(gameover, "gameover");
    SDL_DestroySurface(text);

    if (!gameover) {
      SDL_Log("Error al crear el texto");
    }
  }
  TTF_CloseFont(font);
  // Aqui empezamos con entt
  auto score_sprite = NaviGame::ctx.tm->getTexture("gameover");
  auto score_source = SDL_FRect{0, 0, (float)score_sprite.get()->w,
                                (float)score_sprite.get()->h};
  auto _gameover = reg.create();

  reg.emplace<GC::Posicion>(
      _gameover, ctx.pantalla.w / 2 - (float)score_sprite.get()->w / 2,
      ctx.pantalla.h / 2 - (float)score_sprite.get()->h / 2);
  reg.emplace<GC::Velocidad>(_gameover, 0.0f, 0.0f);
  reg.emplace<GC::Sprite>(_gameover, score_sprite, score_source);
  reg.emplace<GC::GameOver>(_gameover);
  return _gameover;
}

#include "../Componentes/Graficos.hpp"
#include "../Componentes/transformadas.hpp"
#include "../Game/NaviGame.hpp"
#include "Entidades.hpp"
#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "Version.h"
#include "entt/entt.hpp"

void Factory::createVersionText(entt::registry &reg, GameContext &ctx) {
  // Creamos el Texto
  auto font = TTF_OpenFont("assets/fonts/arial.ttf", 36.0f);
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
  auto textsourc = SDL_FRect{0, 0, (float)textversion.get()->w + 10.0f,
                             (float)textversion.get()->h};
  auto _textversion = reg.create();

  reg.emplace<GC::Posicion>(_textversion,
                            ctx.pantalla.w - (textversion->w + 30.0f),
                            ctx.pantalla.h - (textversion->h + 20.0f));
  reg.emplace<GC::Velocidad>(_textversion, 0.0f, 0.0f);
  reg.emplace<GC::Sprite>(_textversion, textversion, textsourc);
}

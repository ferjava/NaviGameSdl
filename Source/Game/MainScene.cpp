#include "MainScene.hpp"
#include "NaviGame.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "Version.h"
#include <memory>
MainScene::MainScene(NaviGame *game) : _game(game) {}

bool MainScene::OnInit() {
  // 1.Inciamos el texturemanager
  _texture.Init(_game->getEngine()->GetRenderer());
  // Cargamos las imagenes
  _nave = _texture.getTexture("assets/images/Naveplayer1.png");
  _nave2 = _texture.getTexture("assets/images/Naveplayer1.png");
  auto font = TTF_OpenFont("assets/fonts/arial.ttf", 10);
  if (!font) {
    SDL_Log("Error no se cargo la fuente ");
    return false;
  }
  auto text = TTF_RenderText_Blended(font, "Version:" VERSION_STRING, 0,
                                     SDL_Color{255, 255, 255});
  if (text) {
    _textversion.reset(
        SDL_CreateTextureFromSurface(_game->getEngine()->GetRenderer(), text),
        SDL_DestroyTexture);
    SDL_SetTextureBlendMode(_textversion.get(), SDL_BLENDMODE_BLEND);
    SDL_DestroySurface(text);
  }
  if (!_textversion) {
    SDL_Log("No se ha creado la texture del texto");
    return false;
  }
  TTF_CloseFont(font);
  return true;
}
void MainScene::OnUpdate(float dt) {
  const bool *keys = SDL_GetKeyboardState(NULL);
  if (keys[SDL_SCANCODE_ESCAPE])
    OnExit();
}
void MainScene::OnRender(SDL_Renderer *renderer) {

  renderer = _game->getEngine()->GetRenderer();
  SDL_FRect navesource{300.0f, 0.0f, 100.0f, 100.0f};
  SDL_FRect nave2source{210.0f, 400.0f, 100.0f, 100.f};
  SDL_FRect navedest{0, 0, 100.0f, 100.0f};
  SDL_FRect nave2dest{300.0f, 300.0f, 100.0f, 100.0f};
  SDL_RenderTexture(renderer, _nave.get(), &navesource, &navedest);
  SDL_RenderTexture(renderer, _nave2.get(), &nave2source, &nave2dest);
  SDL_FRect textdest;
  // SDL_GetTextureSize(_textversion.get(), &textdest.w, &textdest.h);
  // textdest.h = 6.0f;
  // textdest.w = 30.0f;
  textdest.x = 600.0f - textdest.w;
  textdest.h = 800.0f - textdest.h;
  SDL_GetTextureSize(_textversion.get(), &textdest.w, &textdest.h);
  SDL_RenderTexture(renderer, _textversion.get(), NULL, &textdest);
}
void MainScene::OnExit() {
  // Liberamos los punteros
  SDL_DestroyTexture(_textversion.get());
  _game->getEngine()->Exit();
}
void MainScene::OnCleanUp() {}

#include "MainScene.hpp"
#include "../Componentes/Graficos.hpp"
#include "../Componentes/transformadas.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "NaviGame.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
MainScene::MainScene(NaviGame *game) : _game(game) {}

bool MainScene::OnInit() {
  // Creamos una entityi)
  _texture.Init(_game->getEngine()->GetRenderer());
  auto sprite = _texture.getTexture("assets/images/Naveplayer1.png");
  SDL_FRect sprite_src{300.0f, 0.0f, 100.0f, 90.0f};
  auto nave = _registro.create();

  _registro.emplace<GC::Posicion>(nave,
                                  _game->getEngine()->GetFWindowWidth() / 2,
                                  _game->getEngine()->GetFWindowHeight() / 2);
  _registro.emplace<GC::Velocidad>(nave, 0.0f, 0.0f);
  _registro.emplace<GC::Sprite>(nave, sprite, sprite_src);
  auto nave2 = _registro.create();
  _registro.emplace<GC::Posicion>(nave2, 25.0f, 25.0f);
  _registro.emplace<GC::Velocidad>(nave2, 0.0f, 10.0f);
  _registro.emplace<GC::Sprite>(nave2, sprite, sprite_src);

  return true;
}
void MainScene::OnUpdate(float dt) {
  const bool *keys = SDL_GetKeyboardState(NULL);
  if (keys[SDL_SCANCODE_ESCAPE])
    OnExit();
  Sistema::Movimiento(_registro, dt);
}
void MainScene::OnRender(SDL_Renderer *renderer) {

  renderer = _game->getEngine()->GetRenderer();
  Sistema::Dibujado(_registro, renderer);
}
void MainScene::OnExit() {
  // Liberamos los punteros

  _game->getEngine()->Exit();
}
void MainScene::OnCleanUp() {}

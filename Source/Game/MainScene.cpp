#include "MainScene.hpp"

#include "../Entidades/Entidades.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "GameContex.hpp"
#include "NaviGame.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"

MainScene::MainScene(NaviGame *game) : _game(game) {}

bool MainScene::OnInit() {
  // Creamos una entityi)
  _texture.Init(NaviGame::ctx.render);
  NaviGame::ctx.tm = &_texture;
  Factory::createPlayer(_registro, NaviGame::ctx);
  Factory::createVersionText(_registro, NaviGame::ctx);
  return true;
}
void MainScene::OnUpdate(float dt) {

  SDL_FRect limite{0.0f, 0.0f, NaviGame::ctx.pantalla.w,
                   NaviGame::ctx.pantalla.h};
  const bool *keys = SDL_GetKeyboardState(NULL);
  if (keys[SDL_SCANCODE_ESCAPE])
    OnExit();
  Sistema::Movimiento(_registro, dt);
  Sistema::Entrada_Teclado(_registro);
  Sistema::Frontera(_registro, limite);
}
void MainScene::OnRender(SDL_Renderer *renderer) {

  renderer = NaviGame::ctx.render;
  Sistema::Dibujado(_registro, renderer);
}
void MainScene::OnExit() {
  // Liberamos los punteros
  _game->getEngine()->Exit();
}
void MainScene::OnCleanUp() {}

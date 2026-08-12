#include "../Game/TitleScene.hpp"
#include "../Componentes/Componentes.hpp"
#include "../Entidades/Entidades.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "MainScene.hpp"
#include "NaviGame.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_scancode.h"
#include <memory>
float wait = 0.0f;
TitleScene::TitleScene(NaviGame *game) : _game(game) {}

bool TitleScene::OnInit() {
  // Iniciar TextureManager
  _texture.Init(NaviGame::ctx.render);
  NaviGame::ctx.tm = &_texture;
  Factory::Title::createTitleImagen(_registro, NaviGame::ctx);
  Factory::Title::createPress(_registro, NaviGame::ctx);
  _mainscene = std::make_unique<MainScene>(_game);
  wait = 0.0f;
  return true;
}
void TitleScene::OnUpdate(float dt) {
  // Coprobamos en teclado
  const bool *keys = SDL_GetKeyboardState(NULL);
  wait += dt;
  if (wait >= 0.5f) {
    if (keys[SDL_SCANCODE_ESCAPE]) {

      _game->getEngine()->Exit();
      OnExit();
    }
    if (keys[SDL_SCANCODE_SPACE]) {
      // Aqui iniciamos el juego
      // 1 Creamos la escena
      NaviGame::ctx.director->Push(std::move(_mainscene));
    }
  }
  // Hacemos blink en texto
  auto view = _registro.view<Title::PressStart, GC::Sprite>();
  for (auto enti : view) {
    auto &sp = view.get<GC::Sprite>(enti);
    Efecto::Blink(sp.sprite.get(), 0.5f, NaviGame::ctx, 1);
  }
}
void TitleScene::OnRender(SDL_Renderer *render) {
  render = NaviGame::ctx.render;
  // Dibujar
  Sistema::Dibujado(_registro, render);
}
void TitleScene::OnExit() {
  // Salimos del juego
  // _game->getEngine()->Exit();
}
void TitleScene::OnCleanUp() {}

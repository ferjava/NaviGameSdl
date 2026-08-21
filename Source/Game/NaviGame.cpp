#include "NaviGame.hpp"
#include "GameConfig.hpp"
#include "GameContex.hpp"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "TitleScene.hpp"
#include <memory>
GameContext NaviGame::ctx = {};
void NaviGame::OnInit(Engine &engine) {
  _engine = &engine;

  SDL_SetWindowFullscreen(_engine->GetWindow(), true);
  SDL_GetRenderLogicalPresentation(
      engine.GetRenderer(), &_width, &_height,
      nullptr); // WARNING:Cambiado para LogicalPresentacion reder en engine
  ctx.pantalla.w = _width;
  ctx.pantalla.h = _height;
  ctx.render = engine.GetRenderer();
  ctx.director = &_scenedirector;
  auto titlescene = std::make_unique<TitleScene>(this);
  _scenedirector.Push(std::move(titlescene));
  while (!_scenedirector.Current()->OnInit()) {
  }
  Pantalla_W = ctx.pantalla.w;
  Pantalla_H = ctx.pantalla.h;
}
void NaviGame::OnUpdate(float deltaTime) {

  ctx.delta_time = &deltaTime;
  _scenedirector.Current()->OnUpdate(deltaTime);
  _scenedirector.ChangePending();
}

void NaviGame::OnRender(SDL_Renderer *renderer) {
  renderer = NaviGame::ctx.render;
  _scenedirector.Current()->OnRender(renderer);
}

void NaviGame::OnCleanup() {}
NaviGame::~NaviGame() = default;
NaviGame::NaviGame() {};

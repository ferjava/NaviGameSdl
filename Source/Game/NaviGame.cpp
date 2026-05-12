#include "NaviGame.hpp"
#include "GameContex.hpp"
#include "MainScene.hpp"
#include "SDL3/SDL_video.h"
#include <memory>

GameContext NaviGame::ctx = {};
void NaviGame::OnInit(Engine &engine) {
  _engine = &engine;

  SDL_SetWindowFullscreen(_engine->GetWindow(), true);
  SDL_GetWindowSize(_engine->GetWindow(), &_width, &_height);
  ctx.pantalla.w = _width;
  ctx.pantalla.h = _height;
  auto mainscene = std::make_unique<MainScene>(this);
  _scenedirector.Push(std::move(mainscene));
  _scenedirector.Current()->OnInit();
}
void NaviGame::OnUpdate(float deltaTime) {

  _scenedirector.Current()->OnUpdate(deltaTime);
}

void NaviGame::OnRender(SDL_Renderer *renderer) {
  renderer = _engine->GetRenderer();
  _scenedirector.Current()->OnRender(renderer);
}

void NaviGame::OnCleanup() {}
NaviGame::~NaviGame() = default;
NaviGame::NaviGame() {};

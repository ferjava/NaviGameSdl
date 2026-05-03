#include "NaviGame.hpp"
#include "MainScene.hpp"
#include <memory>

void NaviGame::OnInit(Engine &engine) {
  _engine = &engine;
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

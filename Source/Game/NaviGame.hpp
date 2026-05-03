#pragma once
#include "../Core/Engine.hpp"
#include "../Core/IGame.hpp"
#include "../Core/SceneManager.hpp"

class NaviGame : public IGame {
private:
  Engine *_engine;
  SceneManager _scenedirector;

public:
  void OnInit(Engine &engine) override;
  void OnUpdate(float deltaTime) override;

  void OnRender(SDL_Renderer *renderer) override;

  void OnCleanup() override;
  Engine *getEngine() { return _engine; };
};

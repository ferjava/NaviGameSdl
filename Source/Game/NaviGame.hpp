#pragma once
#include "../Core/Engine.hpp"
#include "../Core/IGame.hpp"
#include "../Core/SceneManager.hpp"
#include "GameContex.hpp"

class NaviGame : public IGame {
public:
  static GameContext ctx;

private:
  Engine *_engine;
  SceneManager _scenedirector;
  int _width, _height;

public:
  NaviGame();
  ~NaviGame();
  void OnInit(Engine &engine) override;
  void OnUpdate(float deltaTime) override;
  float GetGameWidth() { return (float)_width; };
  float GetGameHeigth() { return (float)_height; };
  void OnRender(SDL_Renderer *renderer) override;

  void OnCleanup() override;
  Engine *getEngine() { return _engine; };
  SceneManager *getSceneManager() { return &_scenedirector; };
};

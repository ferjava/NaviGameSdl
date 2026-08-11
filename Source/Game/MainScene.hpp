#pragma once
#include "../Core/IScene.hpp"
#include "../Core/TextureManager.hpp"
#include "SDL3/SDL_events.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
class NaviGame;
class MainScene : public IScene {
public:
  MainScene(NaviGame *game);
  // IScene
  bool OnInit() override;
  void OnStart();
  void OnMenuIntro();
  void OnUpdate(float dt) override;
  void OnRender(SDL_Renderer *render) override;
  void OnCleanUp() override;
  void OnExit() override;

private:
  TextureManager _texture;
  NaviGame *_game;          //< Juego al que pertenece las escena
  entt::registry _registro; // El mundo en EnTT
  SDL_Event _event;
};

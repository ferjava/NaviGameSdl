#pragma once
#include "../Core/IScene.hpp"
#include "../Core/TextureManager.hpp"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
class NaviGame;
class MainScene : public IScene {
public:
  MainScene(NaviGame *game);
  // IScene
  bool OnInit() override;

  void OnUpdate(float dt) override;
  void OnRender(SDL_Renderer *render) override;
  void OnCleanUp() override;
  void OnExit() override;

private:
  TextureManager _texture;
  NaviGame *_game;          //< Juego al que pertenece las escena
  entt::registry _registro; // El mundo en EnTT
};

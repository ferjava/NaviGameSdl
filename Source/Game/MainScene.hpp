#pragma once
#include "../Core/IScene.hpp"
#include "../Core/TextureManager.hpp"
#include "SDL3/SDL_render.h"
#include <memory>
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
  NaviGame *_game; //< Juego al que pertenece las escena
  std::shared_ptr<SDL_Texture> _nave;
  std::shared_ptr<SDL_Texture> _textversion;
  std::shared_ptr<SDL_Texture> _nave2;
};

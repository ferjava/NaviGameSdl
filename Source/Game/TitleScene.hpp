#pragma once

#include "../Core/IScene.hpp"
#include "../Core/TextureManager.hpp"
#include "MainScene.hpp"
#include "NaviGame.hpp"
#include "SDL3/SDL_events.h"
#include "entt/entt.hpp"
#include <memory>
//@brief ESta  esta clase crea un objeto  para l pantalla del titulo
// donde se mostrara un titulo y un mensaje parpadeando de que pulses
// la tecla scpace para iniciar el juego
class NaviGame; // Clase para la declaracion
class TitleScene : public IScene {
public:
  TitleScene(NaviGame *game);
  bool OnInit() override;
  void OnUpdate(float dt) override;
  void OnRender(SDL_Renderer *render) override;
  void OnCleanUp() override;
  void OnExit() override;

private:
  TextureManager _texture;
  NaviGame *_game;
  SDL_Event _event;
  entt::registry _registro;
  std::unique_ptr<IScene> _mainscene;
};

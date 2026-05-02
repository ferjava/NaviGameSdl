#pragma once

//
// @brief: Esta interface se usa como base para poder crear scenas
// para nuestro juego
//
#include "SDL3/SDL_render.h"
class IGame;
class IScene {
public:
  virtual ~IScene() = default;
  ///
  ///@brief: Es fuccion se encarga de iniciar los recursos
  /// de la escena y como parametro pide la direccion del juego donde
  /// se actua esta escena
  virtual void OnInit(IGame *game) = 0;
  ///
  ///@brief Esta fucion se repetira y actaulizara en el tiempo de vida
  /// del juego
  ///@param dt Es el tiempo transcurrido desde que se inicio el programa
  ///
  virtual void OnUpdate(float dt) = 0;
  //
  //@brief : Esta funcion se encarga de renderizar las imagenes de la escena
  //@param : direccion de renderer donde los copiaremos nuestras imagenes
  virtual void OnRender(SDL_Renderer *render) = 0;
  //
  //@brief: Esta funcion se encargara de liberar recursos de la escena
  //
  virtual void OnCleanUp() = 0;
  //
  //@brief : funcion para salir de la escena
  //
  virtual void OnExit() = 0;
};

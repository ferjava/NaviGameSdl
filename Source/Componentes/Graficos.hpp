#pragma once
#include "../Game/GameContex.hpp"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "entt/entt.hpp"
#include <functional>
#include <memory>
namespace GC {
/// @brief: Determina la asociacion de una SDL_Textura y el recorte de esta
/// @param  sprite Textura(archivo imagen )
/// @param source SDL_FRect recuadro de la imagen que queremos que se vea
/// @param dest SDL_FRect*  lugar del destino donde se muestra la imagen y el
/// tamaño que le asignamos (podemos aumentar o reducir el tamaño de la imagen
/// )si es nullptr es el tamaño del sprite
struct Sprite {
  std::shared_ptr<SDL_Texture> sprite;
  SDL_FRect source;
  SDL_FRect dest = {0, 0, -1,
                    -1}; // Para que se considere vacio (w =-1 o h = -1)
};
struct Collidable {
  bool isColliding = false;
  SDL_FRect BoxCollidable;
  std::function<void(entt::registry &reg, entt::entity &enitidad,
                     std::vector<entt::entity> &destructor, GameContext &ctx)>
      alcolisonar;
};
} // namespace GC

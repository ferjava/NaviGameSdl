#pragma once

///
/// @brief: En este archivo definimos componentes donde la maquina realiza
/// aciones
#include "../Game/GameContex.hpp"
#include "entt/entity/fwd.hpp"
#include "transformadas.hpp"
#include <functional>
#include <vector>
namespace IA {
struct PosChange {
}; //@brief tags que se añade cuando cambia de una posicion a otra
struct MoveEnd {
}; //@brief tags que se añade cuando se termina el movimiento el bucle
struct Dispara {

  float turno_time; // determina el tiempo hasta que vuelva a intentar disparar
  int dado_disparo; // probabilidad de disparo (comparacion con un dado de 10)
  //@brief: funcion para crear la bala.
  //@param entidad la que crea la bala
  //@param reg registro de entt para añadir la bala
  //@param ctx  structura con referancia a varias variables importantes del
  // juego
  std::function<void(entt::entity &entidad, entt::registry &reg,
                     GameContext &ctx)>
      disparo;

  bool ha_disparado = false;
  float lanzadado = 0.0f;
};
struct Live {
  int lives = 3;

  int Heal = 0; // por defecto
  bool is_live = true;
  // Por defecto
};
//@breif : Moviment es un componente que determina el lugar
// donde se movera la entidad de forma automatica
//@param : destino es un vector que contendra  las direcciones hasta donce
// se desplazara nuestra nave
//
struct Moviment {
  std::vector<GC::Posicion> destino;
  bool repeat = false; //<@param Repite el movimento
  int indice = 0;      // primer elemento
};
} // namespace IA

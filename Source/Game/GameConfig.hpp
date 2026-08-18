#pragma once

#include "../Componentes/Componentes.hpp"
#include "NaviGame.hpp"
#include "SDL3/SDL_rect.h"
#include <syncstream>
#include <vector>
/*
 * En este archivo se pondran  los tamaños de la texturas la velocidad
 * asi con modificar el valor lo modificamos en las entidades del juego
 * */
inline float Pantalla_W = NaviGame::ctx.pantalla.w;
inline float Pantalla_H = NaviGame::ctx.pantalla.h;
namespace Game {
constexpr float TIME_OLEADA = 5.0f;
constexpr int NUMERO_DE_OLEADAS = 30;
constexpr float MOVIMIENTO_SPEED_X = 300.0f;
constexpr float MOVIMIENTO_SPEED_Y = 300.0f;
constexpr GC::Velocidad VELO(MOVIMIENTO_SPEED_X, MOVIMIENTO_SPEED_Y);
namespace Player {
constexpr int LIVES = 3;
constexpr float TEXTURE_W = 90.0f;
constexpr float TEXTURE_H = 90.0f;
inline float VELOCIDAD_X = 100.0f;
constexpr float SPEED = 300.0f; // Velocidad de movimiento al pulsar el teclado

inline std::vector<float> ANIMACION = {0, 100, 200, 300, 400, 500, 600};
inline int SCORE = 0;
} // namespace Player
namespace Enemy {

constexpr float TEXTURE_W = 24.0f;
constexpr float TEXTURE_H = 24.0f;
inline float VELOCIDAD_X = 300.0f;
constexpr float MOVE_RIGHT = (6 * Game::Enemy::TEXTURE_W) + 400.0f;
constexpr float MOVE_LEFT = (0 * Game::Enemy::TEXTURE_W) + 400.0f;
namespace Straight {

inline float VELOCIDAD_X = 300.0f;
inline float VELOCIDAD_Y = 300.0f;
constexpr float MOVE_RIGHT = (6 * Game::Enemy::TEXTURE_W) + 400.0f;
constexpr float MOVE_LEFT = (0 * Game::Enemy::TEXTURE_W) + 400.0f;
constexpr float MOVE_CENTER = (3 * Game::Enemy::TEXTURE_W) + 400.0f;
constexpr int Grupo = 6;              //< determina cuantos iran en un grupo
constexpr float TIME_TO_SHOOT = 1.0f; // tiempo con para lanzar dado
constexpr int VALOR_MAX_DISPARO = 3;  // valor que comparamos con un dado de 10
constexpr float VELOCIDAD_BALA = 100.0f; // Velocidad de la bala
constexpr float TIME_DO_SHOOT = 2.0f;    // Tiempo para volver a disparar
} // namespace Straight
/////////////////////////////////////////////////////////////////////////////
// RAPTOR
////////////////////////////////////////////////////////////////////////////

namespace Raptor {
constexpr float SPRITE_POS_X =
    0.0f; // Lugar de la imagen en el sprite (horizontal )
constexpr float SPRITE_POS_Y =
    0.0f; // Lugar de la imagen en el sprite (vertical )
constexpr float TEXTURE_W = 125.0f; // Anchura textura
constexpr float TEXTURE_H = 100.0f; // Altura textura
constexpr float TIME_TO_SHOOT =
    1.0f; // Tiempo que usa para volver a lanzar el dado
constexpr float TIME_DO_SHOOT = 2.0f; // tiempo para poder volver a disparar
constexpr int CARA_DADO_DISPARA =
    3;                // Valor aleatorio de entre 10 si es menor o igual dispara
inline int LIVES = 1; // Numero de vidas de las que dispone
inline int HEAL_MAX = 30; // Heal que tiene

} // namespace Raptor

inline struct boss {
  // Posiciones  de la animacion inicial  del boss
  std::vector<GC::Posicion> _pos = {{Pantalla_W * 1 / 4, 0.0f},
                                    {Pantalla_W * 1 / 4, Pantalla_H * 1 / 4},
                                    {Pantalla_W * 1 / 4, Pantalla_H * 1 / 2},
                                    {Pantalla_W * 1 / 2, Pantalla_H * 1 / 2},
                                    {Pantalla_W * 1 / 2, Pantalla_H * 1 / 3}};
  // Origen de los distitntos sprite de la animacion  inicial del boss
  std::vector<SDL_FRect> _sprite_src{
      SDL_FRect(0.0f, 0.0f, 120.0f, 50.0f),
      SDL_FRect(0.0f, 80.0f, 170.0f, 65.0f), SDL_FRect(375, 75, 170, 65),
      SDL_FRect(380, 0.0f, 180, 55), SDL_FRect(0.0, 170, 175, 145)};
  int HEAL_MAX = 100;
  float TIME_TO_SHOOT = 3.0f; // Tiempo de espera para disparar
  float TIME_DO_SHOOT = 2.0f; // Tiempo para velver a activar el disparo +
  int DADO_VALOR = 3;         // Valor maximo para disparar (explicacion cuando
                      // cunmple TIME_TO_SHOOT se lanza un dado si el velor
  // es <= DADO_VALOR se dispara ,sino se vuelve a lanzar al cumplir
  // TIME_TO_SHOOT)TIME_DO_SHOOT es elo tiempo de recarga del disparo
  GC::Velocidad _vel = {300.0f, 300.0f};
  ::IA::Live _live = {1, 100};

} BOSS;
} // namespace Enemy
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace Bala {

constexpr float VELOCIDAD_BALA = 500.0f;
constexpr float TAMANO_BALA = 8.0f;

} // namespace Bala
// namespace Bala
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace Explosion {
constexpr float TEXTURE_W = 18.0f;
constexpr float TEXTURE_H = 18.0f;
inline std::vector<float> SOURCE_X = {2,
                                      (TEXTURE_W + 1) * 1,
                                      (TEXTURE_W + 1) * 2,
                                      (TEXTURE_W + 1) * 3,
                                      (TEXTURE_W + 1) * 4,
                                      (TEXTURE_W + 1) * 5};
constexpr float SOURCE_Y = 55.0f;
} // namespace Explosion
} // namespace Game

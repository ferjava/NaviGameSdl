#pragma once
#include <vector>
/*
 * En este archivo se pondran  los tamaños de la texturas la velocidad
 * asi con modificar el valor lo modificamos en las entidades del juego
 * */
namespace Game {
namespace Player {

constexpr float TEXTURE_W = 90.0f;
constexpr float TEXTURE_H = 90.0f;
inline float VELOCIDAD_X = 100.0f;
constexpr float SPEED = 300.0f; // Velocidad de movimiento al pulsar el teclado

inline std::vector<float> ANIMACION = {0, 100, 200, 300, 400, 500, 600};
} // namespace Player
namespace Enemy {

constexpr float TEXTURE_W = 24.0f;
constexpr float TEXTURE_H = 24.0f;
inline float VELOCIDAD_X = 100.0f;
constexpr float MOVE_RIGHT = (6 * Game::Enemy::TEXTURE_W) + 400.0f;
constexpr float MOVE_LEFT = (0 * Game::Enemy::TEXTURE_W) + 400.0f;

} // namespace Enemy
namespace Bala {

constexpr float VELOCIDAD_BALA = 400.0f;
constexpr float TAMANO_BALA = 8.0f;

} // namespace Bala

} // namespace Game

#pragma once

/**
 * @brief : Archivo de declaracion de entidades del juego
 **/
#include "../Game/GameContex.hpp"
#include "entt/entity/fwd.hpp"
namespace Factory {
void createPlayer(entt::registry &reg, GameContext &ctx);
void createVersionText(entt::registry &reg, GameContext &ctx);
} // namespace Factory
